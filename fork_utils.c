/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 20:30:42 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_an_error(t_cmd *cmd, int i);

void	free_stuff(t_cmd *cmd, char *path, int (*pipes)[2])
{
	free(path);
	free(pipes);
	free_ptr_arr(cmd->new_env);
	free_cmd(cmd);
}

void	update_env(t_cmd *cmd, int i)
{
	int		lvl;
	char	*shlvl;

	lvl = 0;
	if (!strcmp_minishell(cmd[i].exec.exec))
	{
		shlvl = _getenv(cmd->new_env, "SHLVL");
		if (!shlvl)
			cmd->new_env = _env(cmd->new_env, "SHLVL=1", cmd);
		else
		{
			lvl = ft_atoi(shlvl) + 1;
			free(shlvl);
			shlvl = ft_itoa(lvl);
			perror_exit(cmd, "malloc at ft_itoa", !shlvl);
			replace_env(cmd->new_env, "SHLVL", shlvl);
			free(shlvl);
		}
	}
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
	}
	if (from >= 0)
	{
		dup2(from, STDIN_FILENO);
	}
}

void	single_child(t_cmd *cmd)
{
	char	*path;
	int		status;

	update_env(cmd, 0);
	status = EXIT_FAILURE;
	if (!cmd[0].exec.exec[0])
		status = EXIT_SUCCESS;
	to_from(cmd);
	init_signals_child();
	path = get_path(cmd, cmd[0].exec.exec);
	stderror_putstr("minishell: ", cmd[0].exec.exec,
		": command not found", !path);
	if (path && !has_an_error(cmd, 0))
		execve(path, cmd[0].exec.argv, cmd->new_env);
	if (path && !dir(path) && !has_an_error(cmd, 0) && cmd[0].exec.exec[0])
		perror_builtins("minishell: ", cmd[0].exec.exec, ": ");
	free(path);
	free_ptr_arr(cmd->new_env);
	free_cmd(cmd);
	exit(status);
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
