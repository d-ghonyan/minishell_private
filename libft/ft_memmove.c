/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:01:27 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 14:35:25 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	overlap(void *dst, void *src, size_t len)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	*last;

	last = src + len - 1;
	s = src;
	d = dst;
	i = 0;
	while (len--)
	{
		if ((d + i == s || d + i == last) || (s + i == d))
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dst;
	s = src;
	if (!src && !dst)
		return (NULL);
	if (overlap(dst, src, len) && d > s)
	{
		d += len - 1;
		s += len - 1;
		while (len--)
		{
			*d = *s;
			s--;
			d--;
		}
		return (dst);
	}
	else if ((overlap(dst, src, len) && d < s)
		|| !overlap(dst, src, len))
		ft_memcpy(dst, src, len);
	return (dst);
}
