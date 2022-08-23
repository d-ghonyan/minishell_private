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

char	*_key(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof (*res) * (find_index(s, '=') + 1));
	if (!res)
	{
		perror("malloc at _key()");
		return (NULL);
	}
	while (s[i] && s[i] != '=')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*_value(char *s)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = find_index(s, '=') + 1;
	res = malloc(sizeof (*res) * (ft_strlen(s) - find_index(s, '=')));
	if (!res)
	{
		perror("malloc at _value()");
		return (NULL);
	}
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}