/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/04 19:41:40 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_main(char **envp, char **argv, char **pwd, struct termios *old);
int		*getstat(void);
char	*getoldpwd(char *oldpwd, int mode);
int		_readline(char **line, char **new_env, int *status, char *pwd);

void	setstat(t_cmd *cmd)
{
	int	err;
	int	i;

	i = -1;
	err = 0;
	if (*(cmd->status) != 0)
		*(getstat()) = *(cmd->status);
	{
		while (++i < cmd->len)
		{
			if (has_an_error(cmd, i))
				err = 1;
		}
		*(getstat()) = err || is_signaled(cmd);
	}
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
		if (_readline(&line, new_env, getstat(), pwd))
			continue ;
		cmd = parse_line(line, envp);
		set_cmd(cmd, line, getstat(), new_env);
		cmd->pwd = pwd;
		cmd->oldpwd = getoldpwd(NULL, 0);
		if (!exec_argv(cmd, 0, 0) || is_signaled(cmd))
			call_forks(cmd, line, getstat());
		if (tcsetattr(0, 0, &old))
			perror("");
		setstat(cmd);
		// *(getstat()) = *(cmd->status);
		new_env = cmd->new_env;
		pwd = cmd->pwd;
		getoldpwd(cmd->oldpwd, 1);
		free_cmd(cmd);
	}
}
