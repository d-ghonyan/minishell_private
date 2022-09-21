/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/21 15:22:16 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	faster_than_printf(char *msg, int signum);

void	print_sig(int status)
{
	if (WTERMSIG(status) == SIGHUP)
		faster_than_printf("Hangup: ", SIGHUP);
	else if (WTERMSIG(status) == SIGQUIT)
		faster_than_printf("Quit: ", SIGQUIT);
	else if (WTERMSIG(status) == SIGILL)
		faster_than_printf("Illegal instruction: ", SIGILL);
	else if (WTERMSIG(status) == SIGTRAP)
		faster_than_printf("Trace/BPT trap: ", SIGTRAP);
	else if (WTERMSIG(status) == SIGABRT)
		faster_than_printf("Abort trap: ", SIGABRT);
	else if (WTERMSIG(status) == SIGBUS)
		faster_than_printf("Bus error: ", SIGBUS);
	else if (WTERMSIG(status) == SIGSEGV)
		faster_than_printf("Segmentation fault: ", SIGSEGV);
	else if (WTERMSIG(status) == SIGSYS)
		faster_than_printf("Bad system call: ", SIGSYS);
	else if (WTERMSIG(status) == SIGFPE)
		faster_than_printf("Floating point exception: ", SIGFPE);
	else if (WTERMSIG(status) == SIGXCPU)
		faster_than_printf("Cputime limit exceeded: ", SIGXCPU);
	else if (WTERMSIG(status) == SIGXFSZ)
		faster_than_printf("Filesize limit exceeded: ", SIGXFSZ);
	else if (WTERMSIG(status) == SIGPROF)
		faster_than_printf("Profiling timer expired: ", SIGPROF);
	ft_putendl_fd("", STDOUT_FILENO);
}

int	free_stuff(t_cmd *cmd, char *path, int (*pipes)[2], int status)
{
	free(path);
	free(pipes);
	free_ptr_arr(cmd->new_env);
	free(cmd->pwd);
	free_cmd(cmd);
	exit(status);
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

	status = EXIT_FAILURE;
	if (!cmd[0].exec.exec[0])
		status = EXIT_SUCCESS;
	to_from(cmd);
	init_signals_child();
	path = get_path(cmd, cmd[0].exec.exec);
	if (!path && !has_an_error(cmd, 0))
		status = not_found(cmd[0].exec.exec);
	if (path && !has_an_error(cmd, 0))
		execve(path, cmd[0].exec.argv, cmd->new_env);
	if (path && !dir(path) && !has_an_error(cmd, 0) && cmd[0].exec.exec[0])
		status = perror_builtins(CE, "minishell: ", cmd[0].exec.exec, ": ");
	if (cmd[0].exec.exec[0] && dir(path))
		status = CE;
	free_stuff(cmd, path, NULL, status);
}

int	fork_loop(char *line, pid_t *pids, t_cmd *cmd, int (*pipes)[2])
{
	int	i;

	i = -1;
	while (++i < count_pipes(line) + 1)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork at call_forks()");
			return (i);
		}
		if (pids[i] == 0)
			children(cmd, pipes, count_pipes(line) + 1, i);
	}
	return (-1);
}
