/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/11 16:10:57 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_stuff(t_cmd *cmd, char *path, int (*pipes)[2], int status);
void	to_from(t_cmd *cmd);
int		fork_loop(char *line, pid_t *pids, t_cmd *cmd, int (*pipes)[2]);
void	single_child(t_cmd *cmd);
void	init_vars(int *status, char **path, t_cmd *cmd, int i);
void	print_sig(int status);
int		fork_error(int i, pid_t *pids, t_cmd *cmd, int (*pipes)[2]);

int	has_an_error(t_cmd *cmd, int i)
{
	int	j;

	j = -1;
	if (!cmd[i].fds)
		return (0);
	while (++j < cmd[i].fds->len)
	{
		if ((!cmd[i].fds[j].heredoc && cmd[i].fds[j].fd < 0)
			|| (cmd[i].fds[j].heredoc && cmd[i].fds[j].fd == -255))
			return (1);
	}
	return (0);
}

int	parent(t_cmd *cmd, int (*pipes)[2], pid_t *pids, int i)
{
	int	count;
	int	status;

	close_pipes_parent(cmd->len - 1, pipes);
	count = 1;
	while (++i < cmd->len)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			*(cmd->status) = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (count && WTERMSIG(status) != SIGPIPE)
				print_sig(status);
			*(cmd->status) = 128 + WTERMSIG(status);
			count = 0;
		}
	}
	return (0);
}

int	children(t_cmd *cmd, int (*pipes)[2], int size, int i)
{
	char	*path;
	int		status;

	init_vars(&status, &path, cmd, i);
	if (dup_pipes(cmd, i, pipes, size - 1))
		return (1);
	if (!is_a_builtin(cmd[i].exec.exec))
	{
		path = get_path(cmd, cmd[i].exec.exec);
		if (!path && !has_an_error(cmd, i))
			status = not_found(cmd[i].exec.exec);
		if (path && !has_an_error(cmd, i))
			execve(path, cmd[i].exec.argv, cmd->envp);
		if (path && !dir(path) && !has_an_error(cmd, i) && cmd[i].exec.exec[0])
			status = perror_builtins(CE,
					"minishell: ", cmd[i].exec.exec, ": ");
		if (cmd[0].exec.exec[0] && dir(path))
			status = CE;
		free_stuff(cmd, path, pipes, status);
	}
	if (!call_builtins(cmd, i, 0))
		status = EXIT_SUCCESS;
	return (free_stuff(cmd, path, pipes, status));
}

int	single_command(t_cmd *cmd)
{
	int		a;
	pid_t	pid;

	if (!is_a_builtin(cmd[0].exec.exec))
	{
		pid = fork();
		if (pid < 0)
		{
			*(cmd->status) = 1;
			return (perror_ret("fork at single_command"));
		}
		if (pid == 0)
			single_child(cmd);
		waitpid(pid, &a, 0);
		if (WIFEXITED(a))
			*(cmd->status) = WEXITSTATUS(a);
		else if (WIFSIGNALED(a))
		{
			print_sig(a);
			*(cmd->status) = 128 + WTERMSIG(a);
		}
		return (0);
	}
	return (call_builtins(cmd, 0, 1));
}

int	call_forks(t_cmd *cmd, char *line)
{
	int		i;
	int		(*pipes)[2];
	pid_t	*pids;

	pids = malloc(sizeof (*pids) * (count_pipes(line) + 1));
	perror_exit(cmd, "malloc failed at call_forks()", !pids);
	if (count_pipes(line) > 0)
	{
		pipes = malloc(sizeof (*pipes) * (count_pipes(line)));
		if (init_pipes(pipes, count_pipes(line), !pipes))
			return (1);
		i = fork_loop(line, pids, cmd, pipes);
		if (i >= 0)
			return (fork_error(i, pids, cmd, pipes));
		parent(cmd, pipes, pids, -1);
		free(pipes);
	}
	else
		single_command(cmd);
	free(pids);
	return (0);
}
