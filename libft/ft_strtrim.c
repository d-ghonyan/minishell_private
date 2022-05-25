/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:38:31 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/16 19:46:34 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	start_index(char const *s, char const *set)
{
	size_t	i;

	i = 0;
	while (s[i] && is_in_set(s[i], set))
		i++;
	return (i);
}

static size_t	reverse_index(char const *s, char const *set)
{
	size_t	i;

	if (start_index(s, set) >= ft_strlen(s))
		return (0);
	i = ft_strlen(s) - 1;
	while (s[i] && is_in_set(s[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	size_t	j;
	char	*res;
	size_t	c;

	if (start_index(s, set) >= ft_strlen(s))
	{
		res = (char *)malloc(1 * sizeof(*res));
		res[0] = '\0';
		return (res);
	}
	i = start_index(s, set);
	j = reverse_index(s, set);
	res = (char *)malloc((j - i + 2) * sizeof(*res));
	if (!res)
		return (NULL);
	c = 0;
	while (i <= j && s[i])
	{
		res[c] = s[i];
		i++;
		c++;
	}
	res[c] = '\0';
	return (res);
}
