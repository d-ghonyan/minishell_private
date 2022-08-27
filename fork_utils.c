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

void	single_child(t_cmd *cmd)
{
	char	*path;

	to_from(cmd);
	init_signals_child();
	path = get_path(cmd, cmd[0].exec.exec);
	stderror_putstr("minishell: ", cmd[0].exec.exec,
		": command not found", !path);
	if (path && !has_an_error(cmd, 0))
		execve(path, cmd[0].exec.argv, cmd->new_env);
	free(path);
	free_ptr_arr(cmd->new_env);
	free_cmd(cmd);
	exit(EXIT_FAILURE);
}

void	to_from(t_cmd *cmd)
{
	int	to;
	int	from;

	to = last_fd(cmd, 0, 1);
	from = last_fd(cmd, 0, 0);
	if (to >= 0)
	{
		dup2(to, STDOUT_FILENO);
		close(to);
	}
	if (from >= 0)
	{
		dup2(from, STDIN_FILENO);
		close(from);
	}
}

int	fork_loop(char *line, pid_t *pids, t_cmd *cmd, int (*pipes)[2])
{
	int	i;

	i = -1;
	while (++i < count_pipes(line) + 1)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror_ret("fork failed at call_forks()"));
		if (pids[i] == 0)
			children(cmd, pipes, count_pipes(line) + 1, i);
	}
	return (0);
}
