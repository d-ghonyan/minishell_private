/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 18:12:18 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fds(t_fds *fds)
{
	int	i;

	i = -1;
	if (!fds)
		return ;
	while (++i < fds->len)
	{
		if (fds[i].fd >= 0)
		{
			if (close(fds[i].fd))
				perror ("close at free_fds()");
		}
		fds[i].fd = -1;
		free(fds[i].here);
		fds[i].here = NULL;
	}
	free(fds);
	fds = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	if (!cmd)
		return ;
	len = cmd->len;
	while (++i < len)
	{
		free(cmd[i].command);
		free(cmd[i].exec.exec);
		free_ptr_arr(cmd[i].exec.argv);
		free_fds(cmd[i].fds);
		cmd[i].command = NULL;
		cmd[i].exec.exec = NULL;
		cmd[i].exec.argv = NULL;
		cmd[i].fds = NULL;
	}
	free(cmd->line);
	free(cmd);
	cmd = NULL;
}
