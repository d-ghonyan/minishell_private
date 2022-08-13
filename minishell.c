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

int	g_status;

int	empty_event(void)
{
}

static char	*ft_strjoin_for_read(char *s, char c)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(*res) * (ft_strlen(s) + 2));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	free(s);
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

char	*read_from_pipe(int pipe)
{
	char	*s;
	char	c;
	int		a;

	s = NULL;
	c = 0;
	a = 0;
	while (1)
	{
		a = read(pipe, &c, 1);
		if (a == -1)
			return (NULL);
		if (a == 0)
			break ;
		s = ft_strjoin_for_read(s, c);
		if (!s)
			break ;
	}
	return (s);
}

// int	loop(t_cmd *cmd, int size, int (*pipes)[2])
// {
// 	int		i;
// 	pid_t	*pids;

// 	i = -1;
// 	pids = malloc(sizeof(*pids) * (size + 1));
// 	if (!pids)
// 		return (perror_ret("malloc failed at loop()"));
// 	while (++i < size)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] < 0)
// 		{
// 			free(pids);
// 			return (perror_ret("pipe failed at loop()"));
// 		}
// 		if (pids[i] == 0)
// 		{
// 			if (children(cmd, pipes, size, i))
// 			{
// 				free(pids);
// 				return (1);
// 			}
// 		}
// 	}
// 	parent(cmd, pipes, pids);
// }

int	main(int argc, char **argv, char **envp)
{
	int		cnf;
	char	*old_line;
	char	*line;
	t_cmd	*cmd;

	cmd = NULL;
	old_line = NULL;
	init_signals_parent();
	rl_event_hook = &empty_event;
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
		exec_argv(cmd);
		cnf = command_not_found(cmd);
		if (cnf >= 0)
			printf("%s: Command not found\n", cmd[cnf].exec.exec);
		else
			call_forks(cmd, line, &g_status);
		free_cmd(cmd);
	}
}
