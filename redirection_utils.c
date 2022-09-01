/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 18:17:43 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err(char c)
{
	ft_putstr_fd("Syntax error near `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "'\n", 2);
	return (1);
}

int	after_red(char *line, int i)
{
	while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_red(char *line)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	while (line[i])
	{
		count = 0;
		if (line[i] == '<' || line[i] == '>')
		{
			c = line[i];
			while (line[i] && line[i] == c)
			{
				i++;
				count++;
			}
			if (count > 2 || !after_red(line, i))
				return (print_err(c));
		}
		i += (line[i] != '\0');
	}
	return (0);
}

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
