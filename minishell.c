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

int	empty_event(void)
{
}

void	change_env(char **envp)
{
	int	i = 0;
	printf("%s\n", getenv("PATH"));
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	envp[i][5] = 'A';
	printf("%s\n", getenv("PATH") ? getenv("PATH") : "null");
}

int	main(int argc, char **argv, char **envp)
{
	char	*old_line;
	char	*line;
	t_cmd	*cmd;

	cmd = NULL;
	old_line = NULL;
	init_signals_parent();
	rl_event_hook = &empty_event;
	// change_env(envp);
	while (1)
	{
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!line)
			return (0);
		if (line[0] && (!old_line || ft_strcmp(line, old_line)))
			add_history(line);
		if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
			continue ;
		old_line = line;
		cmd = parse_line(line, envp);
		if (!cmd)
		{
			perror("malloc failed at parse_line()");
			continue ;
		}
		cmd->status = &g_status;
		if (!exec_argv(cmd))
		{
			printf("%d\n", is_a_builtin(cmd->exec.exec));
			// if (command_not_found(cmd) >= 0)
			// 	printf("%s: Command not found\n",
			// 		cmd[command_not_found(cmd)].exec.exec);
			// else
			// 	call_forks(cmd, line, &g_status);
		}
		free_cmd(cmd);
	}
}
