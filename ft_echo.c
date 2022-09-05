/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:49:18 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/05 13:02:41 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	newline(char *s)
{
	int	j;

	j = 1;
	if (s[0] != '-')
		return (0);
	while (s[j])
	{
		if (s[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, int i, int single)
{
	int	j;
	int	nl;
	int	to;

	j = 1;
	nl = 0;
	to = last_fd(cmd, i, 1);
	if (to < 0 || !single)
		to = STDOUT_FILENO;
	while (cmd[i].exec.argv[j] && newline(cmd[i].exec.argv[j]))
	{
		nl = 1;
		j++;
	}
	while (cmd[i].exec.argv[j])
	{
		ft_putstr_fd(cmd[i].exec.argv[j], to);
		j++;
		if (j != ptr_arr_len(cmd[i].exec.argv))
			ft_putstr_fd(" ", to);
	}
	if (!nl)
		ft_putendl_fd("", to);
	*(cmd->status) = 0;
	return (0);
}
