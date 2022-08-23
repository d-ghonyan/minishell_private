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

int	g_status = 0;

void	thing(void)
{
	struct termios	term;

	if (tcgetattr(0, &term))
		perror ("");
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &term))
		perror ("");
}

int empty_event(void)
{
	return (0);
}

void	sigint_p(int signum)
{
	// rl_done = 1;
	g_status = -1;
}

char	*_readline(char *prompt)
{
	char	*line;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int		status;
	char	*old_line;
	char	*line;
	char	**new_env;
	t_cmd	*cmd;

	cmd = NULL;
	old_line = NULL;
	new_env = NULL;
	init_signals_parent();
	thing();
	// rl_event_hook = &empty_event;
	// change_env(envp);
	while (1)
	{
		for (int i = 0; i < ptr_arr_len(new_env); i++)
			printf("%s\n", new_env[i]);
		g_status = 0;
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!line)
		{
			free_ptr_arr(new_env);
			free(old_line);
			return (0);
		}
		if (line[0] && (!old_line || ft_strcmp(line, old_line)))
		{
			char *temp = old_line;
			old_line = ft_strdup(line);
			free(temp);
			add_history(line);
		}
		if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
		{
			free(line);
			continue ;
		}
		cmd = parse_line(line, envp);
		if (!cmd)
			continue;
		cmd->status = &status;
		cmd->new_env = new_env;
		// call_builtins(cmd, 0);
		if (!exec_argv(cmd, 0, 0))
		{
			call_forks(cmd, line, &status);
		}
		new_env = cmd->new_env;
		// printf("%s\n", (buf = getcwd(NULL, 0)));
		// free(buf);
		free_cmd(cmd);
		free(line);
	}
}

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