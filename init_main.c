/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 18:57:56 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_event(void)
{
	return (0);
}

char	**init_main(char **envp, char **argv, char **pwd, struct termios *old)
{
	char	**new_env;

	(void)argv;
	if (tcgetattr(0, old))
		perror("minishell: ");
	new_env = copy_env(envp, -1);
	init_signals_parent();
	rl_event_hook = &empty_event;
	rl_catch_signals = 0;
	*pwd = getcwd(NULL, 0);
	return (new_env);
}

void	set_cmd(t_cmd *cmd, char *line, int *status, char **new_env)
{
	cmd->line = line;
	cmd->status = status;
	cmd->new_env = new_env;
}

int	*getstat(void)
{
	static int	status = 0;

	return (&status);
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
