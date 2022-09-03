/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:59:34 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/14 20:11:28 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	res = (char *)malloc((i + 1) * sizeof (*s1));
	if (!res)
	{
		perror("malloc at strdup");
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
