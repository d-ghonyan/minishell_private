/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 18:55:37 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit_free(t_cmd *cmd, char *s, char *msg, int cond)
{
	if (cond)
	{
		if (cmd)
			free_ptr_arr(cmd->new_env);
		free_cmd(cmd);
		free(s);
		perror(msg);
		exit(EXIT_FAILURE);
	}
}
