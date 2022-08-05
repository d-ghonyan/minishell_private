/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:53:56 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/10 16:54:11 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *s1, const char *s2, size_t *i)
{
	int	j;

	j = 0;
	while (s2[j])
	{
		s1[*i] = s2[j];
		j++;
		*i += 1;
	}
	s1[*i] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	size_t	i;
	char	*res;

	i = 0;
	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof (*s1));
		s1[0] = '\0';
	}
	res = (char *)malloc(sizeof (*res) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	free((void *)s1);
	ft_strcpy(res, s2, &i);
	return (res);
}
