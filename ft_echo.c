/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:49:18 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 19:34:32 by dghonyan         ###   ########.fr       */
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

int	ft_echo(t_cmd *cmd, int i)
{
	int	j;
	int	nl;

	j = 1;
	nl = 0;
	while (cmd[i].exec.argv[j] && newline(cmd[i].exec.argv[j]))
	{
		nl = 1;
		j++;
	}
	while (cmd[i].exec.argv[j])
	{
		printf("%s", cmd[i].exec.argv[j]);
		j++;
		if (j != ptr_arr_len(cmd[i].exec.argv))
			printf(" ");
	}
	if (!nl)
		printf("\n");
	*(cmd->status) = 0;
	return (0);
}
