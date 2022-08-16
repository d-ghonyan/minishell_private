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

int empty_event(void)
{
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
	// init_signals_pa'rent();
	rl_event_hook = &empty_event;
	// change_env(envp);
	while (1)
	{
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
		if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
			continue;
		cmd = parse_line(line, envp);
		for (int i = 0; i < cmd->len; i++)
			cmd[i].fds = open_files(line);
		for (int i = 0; redirection_count(line) > 0 && i < cmd->fds->len; i++)
		{
			printf("| fd: %d append: %d from: %d to: %d heredoc: %d quoted: %d limiter: %s  |\n\n", cmd->fds[i].fd, cmd->fds[i].append, cmd->fds[i].from, cmd->fds[i].to, cmd->fds[i].heredoc, cmd->fds[i].quoted, cmd->fds[i].here);
		}
		if (!cmd)
			continue;
		cmd->status = &status;
		// if (!exec_argv(cmd))
		// {
		// 	// printf("%d\n", is_a_builtin(cmd->exec.exec));
		// 	if (command_not_found(cmd) >= 0)
		// 		printf("%s: Command not found\n",
		// 			cmd[command_not_found(cmd)].exec.exec);
		// 	else
		// 		call_forks(cmd, line, &status);
		// }
		// printf("%s\n", (buf = getcwd(NULL, 0)));
		// free(buf);
		free_cmd(cmd);
		free(line);
	}
}
