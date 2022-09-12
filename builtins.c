/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/12 11:51:12 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, int i, int single);
int	ft_unset(t_cmd *cmd, int k);
int	ft_cd(t_cmd *cmd, char **argv);
int	ft_export(t_cmd *cmd, int i, int single);
int	ft_exit(t_cmd *cmd, int i, int single);

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
		if (!envp && ft_strcmp_env(cmd->new_env[j], "_"))
		{
			ft_putstr_fd("declare -x ", to);
			export_print(cmd->new_env[j], to);
			ft_putendl_fd("", to);
		}
		else if (envp)
		{
			if (ft_strchr(cmd->new_env[j], '='))
				ft_putendl_fd(cmd->new_env[j], to);
		}
	}
	*(cmd->status) = 0;
	return (0);
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
