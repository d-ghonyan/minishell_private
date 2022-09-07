/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/07 13:45:23 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		empty_event(void);
void	update_env(char ***_env);

int	*getstat(void)
{
	static int	status = 0;

	return (&status);
}

char	**init_main(char **envp, char **argv, char **pwd, struct termios *old)
{
	char	**new_env;
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	perror_exit(NULL, "getcwd at init_main", !cwd);
	if (tcgetattr(0, old))
		perror("tcgetattr: ");
	new_env = copy_env(envp, -1, cwd);
	init_signals_parent();
	rl_event_hook = &empty_event;
	rl_catch_signals = 0;
	*pwd = getcwd(NULL, 0);
	free(cwd);
	update_env(&new_env);
	return (new_env);
}

void	setstat(t_cmd *cmd)
{
	int	err;
	int	i;

	i = -1;
	err = 0;
	if (*(cmd->status) != 0)
		*(getstat()) = *(cmd->status);
	else
	{
		while (++i < cmd->len)
		{
			if (has_an_error(cmd, i))
				err = 1;
		}
		*(getstat()) = (err || is_signaled(cmd));
	}
}

void	set_cmd(t_cmd *cmd, char *line, int *status, char **new_env)
{
	cmd->line = line;
	cmd->status = status;
	cmd->new_env = new_env;
}

char	*getoldpwd(char *oldpwd, int mode)
{
	static char	*stat = NULL;

	if (mode)
	{
		stat = oldpwd;
		return (NULL);
	}
	else
		return (stat);
}
