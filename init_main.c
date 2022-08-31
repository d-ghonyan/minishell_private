/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/31 19:29:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_event(void)
{
	return (0);
}

char	**init_main(char **envp, char **argv)
{
	char	**new_env;

	(void)argv;
	new_env = copy_env(envp);
	init_signals_parent();
	rl_event_hook = &empty_event;
	rl_catch_signals = 0;
	return (new_env);
}

void	set_cmd(t_cmd *cmd, char *line, int *status, char **new_env)
{
	cmd->line = line;
	cmd->status = status;
	cmd->new_env = new_env;
}
