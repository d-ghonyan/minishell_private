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

char	*alloc_command(char *line, int i, int size, int j)
{
	char	*s;

	s = malloc(sizeof (*s) * size);
	if (!s)
		return (NULL);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '\'')
				s[j++] = line[i++];
		}
		if (line[i] == '"')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '"')
				s[j++] = line[i++];
		}
		s[j++] = line[i++];
	}
	s[j] = '\0';
	return (s);
}
