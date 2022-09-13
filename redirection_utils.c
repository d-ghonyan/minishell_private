/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/12 14:30:52 by dghonyan         ###   ########.fr       */
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

int	redirection_count(char *s, int i, int count)
{
	while (s[i])
	{
		if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				;
		if (s[i] == '"')
			while (s[++i] && s[i] != '"')
				;
		if (s[i] && (s[i] == '>' || s[i] == '<'))
		{
			while (s[i] && (s[i] == '>' || s[i] == '<'))
				i++;
			while (s[i] && ft_isspace(s[i]))
				i++;
			if (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
			{
				count++;
				while (s[i] && !ft_isspace(s[i])
					&& s[i] != '<' && s[i] != '>')
					i++;
			}
		}
		i += (s[i] != '\0');
	}
	return (count);
}
