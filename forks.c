/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/29 17:06:00 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_from(t_cmd *cmd);
void	fork_loop(char *line, pid_t *pids, t_cmd *cmd, int (*pipes)[2]);
void	single_child(t_cmd *cmd);
void	free_stuff(t_cmd *cmd, char *path, int (*pipes)[2]);
void	update_env(t_cmd *cmd, int i);

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
		if (WIFEXITED(status))
			*(cmd->status) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
				*(cmd->status) = 128 + WTERMSIG(status);
		i++;
	}
	return (0);
}

int	children(t_cmd *cmd, int (*pipes)[2], int size, int i)
{
	char	*path;
	int		status;

	path = NULL;
	status = EXIT_FAILURE;
	if (!cmd[i].exec.exec[0])
		status = EXIT_SUCCESS;
	perror_exit(cmd, "", dup_pipes(cmd, i, pipes, size - 1));
	init_signals_child();
	if (!is_a_builtin(cmd[i].exec.exec))
	{
		path = get_path(cmd, cmd[i].exec.exec);
		stderror_putstr("minishell: ", cmd[i].exec.exec,
			": command not found", !path);
		if (path && !has_an_error(cmd, i))
			update_env(cmd, i);
		if (path && !has_an_error(cmd, i))
			execve(path, cmd[i].exec.argv, cmd->envp);
		if (path && !dir(path) && !has_an_error(cmd, i) && cmd[i].exec.exec[0])
			perror_builtins("minishell: ", cmd[i].exec.exec, ": ");
		free_stuff(cmd, path, pipes);
		exit(status);
	}
	if (!call_builtins(cmd, i, 0))
		status = EXIT_SUCCESS;
	free_stuff(cmd, path, pipes);
	exit(status);
}

int	single_command(t_cmd *cmd, int *status)
{
	int		a;
	pid_t	pid;

	(void)status;
	if (!is_a_builtin(cmd[0].exec.exec))
	{
		pid = fork();
		if (pid < 0)
			return (perror_ret("fork at single_command"));
		if (pid == 0)
			single_child(cmd);
		else
		{
			waitpid(pid, &a, 0);
			if (WIFEXITED(a))
				*(cmd->status) = WEXITSTATUS(a);
			else if (WIFSIGNALED(a))
				*(cmd->status) = 128 + WTERMSIG(a);
			return (0);
		}
	}
	return (call_builtins(cmd, 0, 1));
}

int	call_forks(t_cmd *cmd, char *line, int *status)
{
	int		(*pipes)[2];
	pid_t	*pids;

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
