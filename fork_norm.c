/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:25:01 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/12 10:52:20 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_error(int i, pid_t *pids, t_cmd *cmd, int (*pipes)[2])
{
	int	stat;
	int	j;

	j = 0;
	while (j < i)
	{
		kill(pids[j], SIGTERM);
		waitpid(pids[j], &stat, 0);
		j++;
	}
	close_pipes_parent(cmd->len - 1, pipes);
	*(cmd->status) = 1;
	free(pipes);
	free(pids);
	return (1);
}

void	init_vars(int *status, char **path, t_cmd *cmd, int i)
{
	*path = NULL;
	*status = EXIT_FAILURE;
	if (!cmd[i].exec.exec[0])
		*status = EXIT_SUCCESS;
	init_signals_child();
}
