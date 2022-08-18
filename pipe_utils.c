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

int	has_an_error(t_cmd *cmd, int i);

int	last_fd(t_cmd *cmd, int i, int cond)
{
	int	to;
	int	from;
	int	j;

	j = -1;
	to = -1;
	from = -1;
	if (!cmd[i].fds)
		return (-1);
	while (++j < cmd[i].fds->len)
	{
		if (cmd[i].fds[j].to)
			to = cmd[i].fds[j].fd;
		if (cmd[i].fds[j].from || cmd[i].fds[j].flags < 0)
			from = cmd[i].fds[j].fd;
	}
	if (cond)
		return (to);
	return (from);
}

int	process_pipes(int i, t_cmd *cmd, int (*pipes)[2])
{
	int	to;
	int	from;

	to = last_fd(cmd, i, 1);
	from = last_fd(cmd, i, 0);
	if (!has_an_error(cmd, i) && cmd[i].fds)
	{
		if (to >= 0)
		{
			if (dup2(to, STDOUT_FILENO) < 0)
				return (perror_ret("dup2 failed --to--"));
		}
		if (from >= 0)
		{
			if (dup2(from, STDIN_FILENO) < 0)
				return (perror_ret("dup2 failed --from--"));
		}
	}
	if (i == 0 && to < 0)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
			return (perror_ret("dup2 failed 1"));
	}
}

int	another_process_pipes(int i, t_cmd *cmd, int (*pipes)[2], int size)
{
	int	to;
	int	from;

	to = last_fd(cmd, i, 1);
	from = last_fd(cmd, i, 0);
	if (i == size && from < 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
			return (perror_ret("dup2 failed 2"));
	}
	else if (i != 0 && i != size)
	{
		if (from < 0)
		{
			if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
				return (perror_ret("dup2 failed 3"));
		}
		if (to < 0)
		{
			if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
				return (perror_ret("dup2 failed 4"));
		}
	}
}

int	dup_pipes(t_cmd *cmd, int i, int (*pipes)[2], int size)
{
	int	to;
	int	from;

	to = last_fd(cmd, i, 1);
	from = last_fd(cmd, i, 0);
	process_pipes(i, cmd, pipes);
	another_process_pipes(i, cmd, pipes, size);
	i = -1;
	while (++i < size)
	{
		if (close(pipes[i][0]) < 0)
			return (perror_ret("close failed at close_pipes 1"));
		if (close(pipes[i][1]) < 0)
			return (perror_ret("close failed at close_pipes 2"));
	}
	return (0);
}

int	init_pipes(int (*pipes)[2], int size, int cond)
{
	int	i;

	i = 0;
	if (cond)
		return (perror_ret("malloc failed at init_pipes()"));
	while (i < size)
	{
		if (pipe(pipes[i]) < 0)
		{
			free(pipes);
			return (perror_ret("pipe failed at init_pipes()"));
		}
		i++;
	}
	return (0);
}
