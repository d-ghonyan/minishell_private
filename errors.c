/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_ret(char *msg)
{
	perror(msg);
	return (1);
}

int	perror_neg(char *msg)
{
	perror(msg);
	return (-1);
}

int	stderror_putstr(char *s1, char *s2, char *s3, int cond)
{
	if (cond)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(s2, 2);
		ft_putendl_fd(s3, 2);
	}
	return (0);
}

int	perror_builtins(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	perror("");
	return (1);
}
