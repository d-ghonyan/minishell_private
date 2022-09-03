/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:25:01 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 15:27:12 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(int *status, char **path, t_cmd *cmd, int i)
{
	*path = NULL;
	*status = EXIT_FAILURE;
	if (!cmd[i].exec.exec[0])
		*status = EXIT_SUCCESS;
	init_signals_child();
}
