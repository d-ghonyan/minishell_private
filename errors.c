/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 17:23:52 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(t_cmd *cmd, char *msg, int cond)
{
	if (cond)
	{
		perror(msg);
		if (cmd)
			free_ptr_arr(cmd->new_env);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
}

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
	return (1);
}

int	perror_builtins(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	perror("");
	return (1);
}
