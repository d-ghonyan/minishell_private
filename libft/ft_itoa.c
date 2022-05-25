/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:41:05 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/16 22:08:57 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_size(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	rec_putstr(char *s, int n, int count)
{
	if (n > 9)
		rec_putstr(s, n / 10, count - 1);
	s[count] = n % 10 + 48;
}

static char	*neg_itoa(int n)
{
	char	*res;

	res = (char *)malloc((ft_size(n) + 2) * sizeof (*res));
	if (!res)
		return (NULL);
	if (n == -2147483648)
	{
		rec_putstr(res, ((n * -1) - 1), ft_size(n));
		res[ft_size(n)] = '8';
	}
	else
		rec_putstr(res, (n * -1), ft_size(n));
	res[ft_size(n) + 1] = '\0';
	res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;

	if (n < 0)
		return (neg_itoa(n));
	if (n == 0)
	{
		res = (char *)malloc(2 * sizeof (*res));
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	res = (char *)malloc((ft_size(n) + 1) * sizeof (*res));
	if (!res)
		return (NULL);
	rec_putstr(res, n, ft_size(n) - 1);
	res[ft_size(n)] = '\0';
	return (res);
}
