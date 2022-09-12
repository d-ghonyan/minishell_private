/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 18:55:37 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit_free(t_cmd *cmd, char *s, char *msg, int cond)
{
	if (cond)
	{
		if (cmd)
		{
			free_ptr_arr(cmd->new_env);
			free(cmd->pwd);
			free(cmd->oldpwd);
		}
		free_cmd(cmd);
		free(s);
		perror(msg);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

void	faster_than_printf(char *msg, int signum)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putnbr_fd(signum, STDERR_FILENO);
}

void	ctrl_d(char **new_env, char *pwd, int *status, char *old_line)
{
	free_ptr_arr(new_env);
	free(pwd);
	free(old_line);
	free(getoldpwd(NULL, 0));
	ft_putendl_fd("exit", STDOUT_FILENO);
	rl_clear_history();
	exit(*status);
}
