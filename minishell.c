/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 15:40:19 by dghonyan         ###   ########.fr       */
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

void	_add_history(char *line)
{
	if (line[0])
		add_history(line);
}

int	_readline(char **line, char **new_env, int *status)
{
	*line = readline(GREEN "minishell" BLUE "$ " RESET);
	if (!(*line))
	{
		free_ptr_arr(new_env);
		exit(EXIT_SUCCESS);
	}
	_add_history(*line);
	if (!(*line[0]) || count_pipes(*line) < 0
		|| check_quotes(*line) || valid_red(*line))
	{
		*status = (g_status == 130);
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}

int	*main_things(void)
{
	static int	status = 0;

	return (&status);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**new_env;
	t_cmd			*cmd;
	struct termios	old;

	if (tcgetattr(0, &old))
		perror("");
	new_env = init_main(envp, argv);
	while (argc)
	{
		if (_readline(&line, new_env, main_things()))
			continue ;
		cmd = parse_line(line, envp);
		set_cmd(cmd, line, main_things(), new_env);
		if (!exec_argv(cmd, 0, 0) || is_signaled(cmd))
			call_forks(cmd, line, main_things());
		if (tcsetattr(0, 0, &old))
			perror("");
		*(main_things()) = *(cmd->status);
		new_env = cmd->new_env;
		free_cmd(cmd);
	}
}
