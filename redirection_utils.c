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

int	redirection_count(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		{
			while (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
				i++;
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			if (cmd[i] && !ft_isspace(cmd[i])
				&& cmd[i] != '<' && cmd[i] != '>')
			{
				count++;
				while (cmd[i] && !ft_isspace(cmd[i])
					&& cmd[i] != '<' && cmd[i] != '>')
					i++;
			}
		}
		i += (cmd[i] != '\0');
	}
	return (count);
}
