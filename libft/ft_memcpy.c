/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:15:14 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/10 20:45:56 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)dest = ((unsigned char *)src)[i];
		dest++;
		i++;
	}	
	return (dest - n);
}
