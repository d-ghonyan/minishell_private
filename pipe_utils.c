#include "minishell.h"

int	dup_pipes(int i, int (*pipes)[2], int size)
{
	if (i == 0)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
			return (perror_ret("dup2 failed 1"));
	}
	else if (i == size)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
			return (perror_ret("dup2 failed 2"));
	}
	else
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0)
			return (perror_ret("dup2 failed 3"));
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0)
			return (perror_ret("dup2 failed 4"));
	}
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
