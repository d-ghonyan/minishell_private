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

int	parent(t_cmd *cmd, int (*pipes)[2], pid_t *pids)
{
	int	i;
	int	status;

	i = -1;
	while (++i < cmd->len - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	i = 0;
	while (i < cmd->len)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return (0);
}

int	children(t_cmd *cmd, int (*pipes)[2], int size, int i)
{
	char	*path;

	if (dup_pipes(i, pipes, size - 1))
		return (1);
	init_signals_child();
	if (!is_a_builtin(cmd[i].exec.exec))
	{
		path = get_path(cmd[i].exec.exec);
		if (path)
			execve(path, cmd[i].exec.argv, cmd->envp);
		free(path);
	}
	else
	{
		call_builtins(cmd, i);
	}
	return (0);
}

int	single_command(t_cmd *cmd, int *status)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		init_signals_child();
		path = get_path(cmd[0].exec.exec);
		if (path)
			execve(path, cmd[0].exec.argv, cmd->envp);
		free(path);
	}
	else
		waitpid(pid, status, 0);
}

int	call_forks(t_cmd *cmd, char *line, int *status)
{
	int		i;
	int		(*pipes)[2];
	pid_t	*pids;
	char	*path;

	i = -1;
	pids = malloc(sizeof(*pids) * (count_pipes(line) + 1));
	if (!pids)
		return (perror_ret("malloc failed at call_forks()"));
	if (count_pipes(line) > 0)
	{
		pipes = malloc(sizeof(*pipes) * (count_pipes(line)));
		if (init_pipes(pipes, count_pipes(line), !pipes))
			return (1);
		while (++i < count_pipes(line) + 1)
		{
			pids[i] = fork();
			if (pids[i] < 0)
				return (perror_ret("fork failed at call_forks()"));
			if (pids[i] == 0)
				children(cmd, pipes, count_pipes(line) + 1, i);
		}
		parent(cmd, pipes, pids);
		free(pipes);
	}
	else
		single_command(cmd, status);
	return (0);
}
