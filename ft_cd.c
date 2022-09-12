/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:32:59 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/12 11:36:18 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_utils(t_cmd *cmd, char *cwd)
{
	replace_env(cmd->new_env, "OLDPWD", cmd->pwd, cmd);
	free(cmd->oldpwd);
	cmd->oldpwd = ft_strdup(cmd->pwd);
	replace_env(cmd->new_env, "PWD", cwd, cmd);
	free(cmd->pwd);
	cmd->pwd = cwd;
	*(cmd->status) = 0;
}

int	_home(t_cmd *cmd)
{
	char	*cwd;
	char	*home;

	home = _getenv(cmd->new_env, "HOME", cmd);
	if (chdir(home) < 0)
	{
		perror_builtins(NF, "cd: ", home, ": ");
		free(home);
		*(cmd->status) = 1;
		return (1);
	}
	cwd = getcwd(NULL, 1);
	if (!cwd)
	{
		perror("getcwd at ft_cd");
		free(home);
		*(cmd->status) = 1;
		return (1);
	}
	cd_utils(cmd, cwd);
	free(home);
	return (0);
}

int	_cd(t_cmd *cmd, char *s)
{
	char	*cwd;

	if (!s[0])
		return (0);
	if (chdir(s) < 0)
	{
		perror_builtins(NF, "cd: ", s, ": ");
		*(cmd->status) = 1;
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd at ft_cd");
		*(cmd->status) = 1;
		return (1);
	}
	cd_utils(cmd, cwd);
	return (0);
}

int	ft_cd(t_cmd *cmd, char **argv)
{
	if (ptr_arr_len(argv) == 1)
		return (_home(cmd));
	return (_cd(cmd, argv[1]));
}
