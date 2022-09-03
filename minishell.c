/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 18:07:42 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_main(char **envp, char **argv, char **pwd, struct termios *old);
int		*getstat(void);
char	*getoldpwd(char *oldpwd, int mode);

int	g_status = 0;

void	sigint_p(int signum)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_status = signum + 128;
}

void	_add_history(char *line)
{
	if (line[0])
		add_history(line);
}

int	_readline(char **line, char **new_env, int *status)
{
	*line = readline(GREEN "minishell" BLUE "$ " RESET);
	if (!(*line))
	{
		free_ptr_arr(new_env);
		exit(EXIT_SUCCESS);
	}
	_add_history(*line);
	if (!(*line[0]) || count_pipes(*line) < 0
		|| check_quotes(*line) || valid_red(*line))
	{
		*status = (g_status == 130);
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}

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
		if (_readline(&line, new_env, getstat()))
			continue ;
		cmd = parse_line(line, envp);
		set_cmd(cmd, line, getstat(), new_env);
		cmd->pwd = pwd;
		cmd->oldpwd = getoldpwd(NULL, 0);
		if (!exec_argv(cmd, 0, 0) || is_signaled(cmd))
			call_forks(cmd, line, getstat());
		if (tcsetattr(0, 0, &old))
			perror("");
		*(getstat()) = *(cmd->status);
		new_env = cmd->new_env;
		pwd = cmd->pwd;
		getoldpwd(cmd->oldpwd, 1);
		free_cmd(cmd);
	}
}
