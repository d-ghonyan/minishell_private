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

void	to_from(t_cmd *cmd);
void	fork_loop(char *line, pid_t *pids, t_cmd *cmd, int (*pipes)[2]);

int	has_an_error(t_cmd *cmd, int i)
{
	int	j;

	j = -1;
	if (!cmd[i].fds)
		return (0);
	while (++j < cmd[i].fds->len)
	{
		if (!cmd[i].fds[j].heredoc && cmd[i].fds[j].fd < 0)
			return (1);
	}
	return (0);
}

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

	if (dup_pipes(cmd, i, pipes, size - 1))
	{
		free(pipes);
		exit(EXIT_FAILURE);
	}
	init_signals_child();
	if (!is_a_builtin(cmd[i].exec.exec))
	{
		path = get_path(cmd[i].exec.exec);
		stderror_putstr(cmd[i].exec.exec, ": not found", "", !path);
		if (path && !has_an_error(cmd, i))
			execve(path, cmd[i].exec.argv, cmd->envp);
		free(path);
		free(pipes);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	exit(call_builtins(cmd, i));
}

int	single_command(t_cmd *cmd, int *status)
{
	char	*path;
	pid_t	pid;

	if (!is_a_builtin(cmd[0].exec.exec))
	{
		pid = fork();
		if (pid == 0)
		{
			to_from(cmd);
			init_signals_child();
			path = get_path(cmd[0].exec.exec);
			stderror_putstr(cmd[0].exec.exec, ": not found", "", !path);
			if (path && !has_an_error(cmd, 0))
				execve(path, cmd[0].exec.argv, cmd->envp);
			free(path);
			free_cmd(cmd);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, status, 0);
	}
	else
		return (call_builtins(cmd, 0));
	return (0);
}

int	call_forks(t_cmd *cmd, char *line, int *status)
{
	int		(*pipes)[2];
	pid_t	*pids;
	char	*path;

	pids = malloc(sizeof (*pids) * (count_pipes(line) + 1));
	if (!pids)
		return (perror_ret("malloc failed at call_forks()"));
	if (count_pipes(line) > 0)
	{
		pipes = malloc(sizeof (*pipes) * (count_pipes(line)));
		if (init_pipes(pipes, count_pipes(line), !pipes))
			return (1);
		fork_loop(line, pids, cmd, pipes);
		parent(cmd, pipes, pids);
		free(pipes);
	}
	else
		single_command(cmd, status);
	free(pids);
	return (0);
}
