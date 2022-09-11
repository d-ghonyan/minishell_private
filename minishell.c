/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/11 18:58:56 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_main(char **envp, char **argv, char **pwd, struct termios *old);
int		*getstat(void);
int		_readline(char **line, char **new_env, int *status, char *pwd);
void	setstat(t_cmd *cmd);

void	init_lvl(int *lvl, char *shlvl, char **env)
{
	char	*newlvl;

	*lvl = ft_atoi(shlvl) + 1;
	if (*lvl < 0)
		*lvl = 0;
	if (*lvl > 1000)
	{
		newlvl = ft_itoa(*lvl);
		if (!newlvl)
		{
			free_ptr_arr(env);
			free(shlvl);
			perror_exit(NULL, "malloc at init_lvl", 1);
		}
		stderror_putstr("minishell: warning: shell level (",
			newlvl, ") too high, resetting to 1", STDOUT_FILENO);
		*lvl = 1;
		free(newlvl);
	}
}

void	update_env(char ***__env)
{
	int		lvl;
	char	*shlvl;
	char	*newlvl;

	lvl = 0;
	while ((*__env)[lvl] && ft_strcmp_env((*__env)[lvl], "SHLVL"))
		lvl++;
	if (!(*__env)[lvl])
		*__env = env(*__env, "SHLVL", "1", NULL);
	else
	{
		shlvl = _value((*__env)[lvl], NULL);
		lvl = ft_atoi(shlvl) + 1;
		init_lvl(&lvl, shlvl, *__env);
		newlvl = ft_itoa(lvl);
		replace_env((*__env), "SHLVL", newlvl, NULL);
		free(newlvl);
		free(shlvl);
	}
}

//start typing a line
//and go back in history
//to get a memory leak

int	main(int argc, char **argv, char **envp)
{
	char			*pwd;
	char			*line;
	char			**new_env;
	t_cmd			*cmd;
	struct termios	old;

	new_env = init_main(envp, argv, &pwd, &old);
	while (argc)
	{
		if (_readline(&line, new_env, getstat(), pwd))
			continue ;
		cmd = parse_line(line, envp);
		set_cmd(cmd, line, getstat(), new_env);
		cmd->pwd = pwd;
		cmd->oldpwd = getoldpwd(NULL, 0);
		if (!exec_argv(cmd, 0, 0) || is_signaled(cmd))
			call_forks(cmd, line);
		if (tcsetattr(0, 0, &old))
			perror("");
		setstat(cmd);
		new_env = cmd->new_env;
		pwd = cmd->pwd;
		getoldpwd(cmd->oldpwd, 1);
		free_cmd(cmd);
	}
}
