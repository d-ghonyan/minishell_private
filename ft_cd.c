/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:32:59 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/29 21:09:30 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_home(t_cmd *cmd)
{
	char	*cwd;
	char	*pwd;
	char	*home;

	// home = _getenv(cmd->new_env, "HOME");
	if (chdir(home) < 0)
	{
		perror_builtins("cd: ", home, ": ");
		*(cmd->status) = 1;
	}
	else
	{
		cwd = getcwd(NULL, 1);
		if (!cwd)
		{
			free(home);
			perror("getcwd at ft_cd");
			*(cmd->status) = 1;
			return (1);
		}
		// pwd = _getenv(cmd->new_env, "PWD");
		if (!pwd)
			cmd->new_env = env(cmd->new_env, "PWD", cwd, cmd);
		else
			replace_env(cmd->new_env, "PWD", cwd);
		*(cmd->status) = 0;
	}
	free(home);
	free(pwd);
	return (0);
}

int	ft_cd(t_cmd *cmd, char **argv)
{
	char	*pwd;
	char	*home;

	if (ptr_arr_len(argv) > 2)
		return (stderror_putstr("Too many arguments", "", "", 1));
	if (ptr_arr_len(argv) == 1)
	{
		// pwd = _getenv(cmd->new_env, "PWD");
		// home = _getenv(cmd->new_env, "HOME");
		if (chdir(home) < 0)
		{
			perror_builtins("cd: ", home, ": ");
			free(home);
			free(pwd);
			*(cmd->status) = 1;
			return (1);
		}
	}
	return (0);
}
