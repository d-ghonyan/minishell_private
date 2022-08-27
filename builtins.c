/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 19:33:00 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd *cmd, int i);
int	ft_unset(t_cmd *cmd, int k);
int	ft_cd(t_cmd *cmd, char **argv);

int	ft_pwd(t_cmd *cmd, int i)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		*(cmd->status) = 1;
		return (perror_ret("getcwd"));
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	*(cmd->status) = 0;
	return (0);
}

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->new_env[++i])
		printf("%s\n", cmd->new_env[i]);
	*(cmd->status) = 0;
	return (0);
}

int	call_builtins(t_cmd *cmd, int i)
{
	char	*s;

	s = cmd[i].exec.exec;
	if (!ft_strcmp(s, "cd"))
		ft_cd(cmd, cmd[i].exec.argv);
	if (!ft_strcmp(s, "pwd"))
		ft_pwd(cmd, i);
	if (!ft_strcmp(s, "export"))
		ft_export(cmd, i);
	if (!ft_strcmp(s, "unset"))
		ft_unset(cmd, i);
	if (!ft_strcmp(s, "env"))
		ft_env(cmd);
	if (!ft_strcmp(s, "echo"))
		ft_echo(cmd, i);
	return (0);
}
