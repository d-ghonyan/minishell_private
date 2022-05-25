/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:44:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/18 20:06:45 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	i;

	res = malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}
