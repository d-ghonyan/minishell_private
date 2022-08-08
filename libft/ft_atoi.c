/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:16:00 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/13 13:00:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\r'
		|| str[i] == '\t'
		|| str[i] == '\v'
		|| str[i] == '\n'
		|| str[i] == '\f'
		|| str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	minus;
	int	res;

	minus = 1;
	res = 0;
	i = ft_isspace_index(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i += 1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * minus);
}
