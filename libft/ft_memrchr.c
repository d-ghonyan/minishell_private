/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 11:47:01 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 11:47:41 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memrchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n - 1)
	{
		s++;
		i++;
	}
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s--;
	}
	return (NULL);
}
