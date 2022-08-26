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

int	ft_cd(char **argv)
{
	if (ptr_arr_len(argv) > 2)
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ptr_arr_len(argv) == 1)
	{
		if (chdir(getenv("HOME")) < 0)
			return (perror_builtins("cd: ", argv[0], ": "));
	}
	else if (chdir(argv[1]) < 0)
		return (perror_builtins("cd: ", argv[1], ": "));
	return (0);
}

int	ft_pwd(t_cmd *cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror_ret("getcwd at ft_pwd()"));
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->new_env[++i])
		printf("%s\n", cmd->new_env[i]);
	return (0);
}

int	ft_echo(t_cmd *cmd, int i)
{
	int	j;
	int	nl;

	j = 1;
	nl = 0;
	while (!ft_strcmp(cmd[i].exec.argv[j++], "-n"))
		nl = 1;
	while (cmd[i].exec.argv[j])
	{
		printf("%s", cmd[i].exec.argv[j]);
		if (j != ptr_arr_len(cmd[i].exec.argv))
			printf(" ");
		j++;
	}
	if (!nl)
		printf("\n");
	return (0)
}

int	call_builtins(t_cmd *cmd, int i)
{
	char	*s;

	s = cmd[i].exec.exec;
	if (!ft_strcmp(s, "cd"))
		*(cmd->status) = ft_cd(cmd[i].exec.argv);
	if (!ft_strcmp(s, "pwd"))
		*(cmd->status) = ft_pwd(cmd);
	if (!ft_strcmp(s, "export"))
		*(cmd->status) = ft_export(cmd, i);
	if (!ft_strcmp(s, "unset"))
		*(cmd->status) = ft_unset(cmd, i);
	if (!ft_strcmp(s, "env"))
		*(cmd->status) = ft_env(cmd);
	if (!ft_strcmp(s, "echo"))
		*(cmd->status) = ft_echo(cmd, i);
	return (0);
}
