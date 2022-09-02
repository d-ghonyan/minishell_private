/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/02 15:09:04 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, int i, int single);
int	ft_unset(t_cmd *cmd, int k);
int	ft_cd(t_cmd *cmd, char **argv);
int	ft_export(t_cmd *cmd, int i, int single);

int	ft_pwd(t_cmd *cmd, int i, int single)
{
	char	*path;
	int		to;

	to = last_fd(cmd, i, 1);
	if (to < 0 || !single)
		to = STDOUT_FILENO;
	path = getcwd(NULL, 0);
	if (!path)
	{
		*(cmd->status) = 1;
		return (perror_ret("getcwd"));
	}
	ft_putendl_fd(path, to);
	free(path);
	*(cmd->status) = 0;
	return (0);
}

int	ft_env(t_cmd *cmd, int i, int envp, int single)
{
	int	j;
	int	to;

	to = last_fd(cmd, i, 1);
	if (to < 0 || !single)
		to = STDOUT_FILENO;
	j = -1;
	while (cmd->new_env[++j])
	{
		if (!envp)
		{
			ft_putstr_fd("declare -x ", to);
			ft_putendl_fd(cmd->new_env[j], to);
		}
		else
		{
			if (ft_strchr(cmd->new_env[j], '='))
				ft_putendl_fd(cmd->new_env[j], to);
		}
	}
	*(cmd->status) = 0;
	return (0);
}

int	ft_exit(t_cmd *cmd, int i, int single)
{
	int	status;

	status = 0;
	if (single)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (ptr_arr_len(cmd[i].exec.argv) > 2)
	{
		*(cmd->status) = 1;
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	else
	{
		status = *(cmd->status);
		if (ptr_arr_len(cmd[i].exec.argv) > 1)
			status = (unsigned char)ft_atoi(cmd[i].exec.argv[1]);
		free_ptr_arr(cmd->new_env);
		free_cmd(cmd);
		exit(status);
	}
}

int	call_builtins(t_cmd *cmd, int i, int single)
{
	char	*s;

	if (has_an_error(cmd, i))
		return (1);
	s = cmd[i].exec.exec;
	if (!ft_strcmp(s, "cd"))
		return (ft_cd(cmd, cmd[i].exec.argv));
	if (!ft_strcmp(s, "pwd"))
		return (ft_pwd(cmd, i, single));
	if (!ft_strcmp(s, "export"))
		return (ft_export(cmd, i, single));
	if (!ft_strcmp(s, "unset"))
		return (ft_unset(cmd, i));
	if (!ft_strcmp(s, "env"))
		return (ft_env(cmd, i, 1, single));
	if (!ft_strcmp(s, "echo"))
		return (ft_echo(cmd, i, single));
	if (!ft_strcmp(s, "exit"))
		return (ft_exit(cmd, i, single));
	return (0);
}
