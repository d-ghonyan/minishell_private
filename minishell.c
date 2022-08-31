/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/31 19:29:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	sigint_p(int signum)
{
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
	if (!(*line[0]) || count_pipes(*line) < 0
		|| check_quotes(*line) || valid_red(*line))
	{
		*status = (g_status == 130);
		g_status = 0;
		free(*line);
		return (1);
	}
	add_history(*line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int				status;
	char			*line;
	char			**new_env;
	t_cmd			*cmd;
	struct termios	old;

	if (tcgetattr(0, &old))
		perror("");
	new_env = init_main(envp, argv);
	while (argc)
	{
		if (_readline(&line, new_env, &status))
			continue ;
		cmd = parse_line(line, envp);
		set_cmd(cmd, line, &status, new_env);
		if (!exec_argv(cmd, 0, 0) || is_signaled(cmd))
			call_forks(cmd, line, &status);
		if (tcsetattr(0, 0, &old))
			perror("");
		status = *(cmd->status);
		new_env = cmd->new_env;
		free_cmd(cmd);
	}
}
	// char *anush = "anush";
	// int i = -1;
	// while (anush[++i])
	// {
	// 	char c = anush[i] - 32;
	// 	if (c == 'A')
	// 		write(1, "asdasdasdasdasd", 200);
	// 	else
	// 		write(1, &c, 1);
	// }
	// printf("\n%s\n", anush);
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