/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:25:01 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/11 15:07:07 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_error(int i, pid_t *pids, t_cmd *cmd)
{
	int	stat;
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &stat, 0);
		j++;
	}
	*(cmd->status) = 1;
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
