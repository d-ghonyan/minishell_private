/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/09 18:59:17 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(t_cmd *cmd, char *msg, int cond)
{
	if (cond)
	{
		perror(msg);
		if (cmd)
		{
			free_ptr_arr(cmd->new_env);
			free(cmd->pwd);
			free(cmd->oldpwd);
		}
		free_cmd(cmd);
		rl_clear_history();
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
	return (-255);
}

int	stderror_putstr(char *s1, char *s2, char *s3, int cond)
{
	if (cond)
	{	
		ft_putstr_fd(s1, STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
		ft_putendl_fd(s3, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	perror_builtins(int status, char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	perror("");
	return (status);
}
