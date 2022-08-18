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

int empty_event(void)
{
}

void	sigint_p(int signum)
{
	rl_done = 1;
	g_status = -1;
}


void change_env(char **envp)
{
	int i = 0;
	printf("%s\n", getenv("PATH"));
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	envp[i][5] = 'A';
	printf("%s\n", getenv("PATH") ? getenv("PATH") : "null");
}

int main(int argc, char **argv, char **envp)
{
	int status;
	char *old_line;
	char *line;
	t_cmd *cmd;
	char *buf;

	cmd = NULL;
	old_line = NULL;
	init_signals_parent();
	rl_event_hook = &empty_event;
	// change_env(envp);
	while (1)
	{
		g_status = 0;
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!line)
		{
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
		if ((rl_done && g_status < 0) || !line[0] || count_pipes(line) < 0 || check_quotes(line))
		{
			free(line);
			continue ;
		}
		cmd = parse_line(line, envp);
		if (!cmd)
			continue;
		cmd->status = &status;
		// exec_argv(cmd);
		// for (int i = 0; i < cmd->len; i++)
		// {
		// 	printf("%s\n", cmd[i].exec.exec);
		// 	for (int j = 0; cmd->fds && j < cmd[i].fds->len; j++)
		// 	{
		// 		// char c[100];
		// 		// int a = read(cmd[i].fds[j].fd, c, 100);
		// 		// c[a] = '\0';
		// 		// write(1, c, ft_strlen(c));
		// 		printf("%d\n", cmd[i].fds[j].fd);
		// 	}
		// }
		if (!exec_argv(cmd))
		{
			// printf("%d\n", is_a_builtin(cmd->exec.exec));
			// if (command_not_found(cmd) >= 0)
			// 	printf("%s: Command not found\n",
			// 		cmd[command_not_found(cmd)].exec.exec);
			// else
				call_forks(cmd, line, &status);
		}
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