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

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = cmd->len;
	while (++i < len)
	{
		free(cmd[i].here_str);
		free(cmd[i].heredoc);
		free(cmd[i].infile);
		free(cmd[i].outfile);
		free(cmd[i].command);
		free(cmd[i].exec.exec);
		free_ptr_arr(cmd[i].exec.argv);
	}
	free(cmd);
}
