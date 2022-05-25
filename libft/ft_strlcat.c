/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:17:42 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 21:29:39 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *s, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = 0;
	i = ft_strlen(dst);
	len = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(s));
	while (s[j] && i < size - 1)
	{
		dst[i] = s[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(s) + len);
}
