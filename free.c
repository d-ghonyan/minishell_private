/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:54 by dghonyan         ###   ########.fr       */
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
		free(fds[i].here);
	}
	free(fds);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = cmd->len;
	while (++i < len)
	{
		free(cmd[i].command);
		free(cmd[i].exec.exec);
		free_fds(cmd[i].fds);
		free_ptr_arr(cmd[i].exec.argv);
	}
	free(cmd);
}

