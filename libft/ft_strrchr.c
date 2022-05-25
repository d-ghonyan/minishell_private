/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:47:22 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 11:47:24 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		s++;
		i++;
	}
	s--;
	while (i)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}
