/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 20:30:49 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	thing(int parent)
{
	struct termios	term;

	if (tcgetattr(0, &term))
		perror ("");
	if (parent)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag &= ECHOCTL;
	if (tcsetattr(0, 0, &term))
		perror ("");
}

int	empty_event(void)
{
	return (0);
}

void	sigint_p(int signum)
{
	write(0, "\b\b", 2);
	rl_replace_line("", 0);
	rl_done = 1;
	g_status = signum + 128;
}

int	_readline(char **line, char **new_env, int *status)
{
	*line = readline(GREEN "minishell" BLUE "$ " RESET);
	if (!(*line))
	{
		free_ptr_arr(new_env);
		exit(EXIT_SUCCESS);
	}
	if (*line[0])
		add_history(*line);
	if (!(*line[0]) || count_pipes(*line) < 0 || check_quotes(*line))
	{
		*status = g_status;
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*line;
	char	**new_env;
	t_cmd	*cmd;

	(void)argv;
	cmd = NULL;
	new_env = copy_env(envp);
	init_signals_parent();
	rl_event_hook = &empty_event;
	while (argc)
	{
		if (_readline(&line, new_env, &status))
			continue ;
		cmd = parse_line(line, envp);
		cmd->line = line;
		cmd->status = &status;
		cmd->new_env = new_env;
		if (!exec_argv(cmd, 0, 0))
			call_forks(cmd, line, &status);
		status = *(cmd->status);
		new_env = cmd->new_env;
		free_cmd(cmd);
	}
}
	// thing(1);

	// int pipes[2];
	// pipe(pipes);
	// write(pipes[1], "asdasdadsasd", 100);
	// int fd = dup(pipes[0]);
	// close(pipes[0]);
	// close(pipes[1]);
	// char c[100];
	// int a = read(fd, c, 10);
	// c[a] = '\0';
	// write(1, c, 10);
	// return (0);
		// line = readline(GREEN "minishell" BLUE "$ " RESET);
		// if (!line)
		// {
		// 	free_ptr_arr(new_env);
		// 	free(old_line);
		// 	return (0);
		// }
		// if (line[0])
		// 	add_history(line);
		// if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
		// {
		// 	status = g_status;
		// 	g_status = 0;
		// 	free(line);
		// 	continue ;
		// }