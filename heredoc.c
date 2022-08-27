/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 18:51:20 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*final_limiter(char *s);
int		here_final_len(char *s, t_cmd *cmd);
int		limiter_quotes(char *s);
void	here_child(char *limiter, int quoted, int pipes[2], t_cmd *cmd);

char	*here_expand(char *s, int i, int j, t_cmd *cmd)
{
	char	*res;

	res = ft_calloc(sizeof(*res), (here_final_len(s, cmd) + 1));
	if (!res)
	{
		free(s);
		perror_exit(cmd, "malloc at here_expand", 1);
	}
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (var_len(s, i + 1, 0) == 0)
				res[j++] = '$';
			else
			{
				strjoin_var(res, expanded_env(s, i + 1, 0, cmd));
				j = ft_strlen(res);
			}
			i += var_len(s, i + 1, 0) + 1;
		}
		if (s[i] != '\0' && s[i] != '$')
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	call_child(char *limiter, int quoted, int pipes[2], t_cmd *cmd)
{
	char	*l;

	l = final_limiter(limiter);
	perror_exit(cmd, "malloc at final_limiter", !l);
	here_child(l, quoted, pipes, cmd);
	free(l);
	exit (EXIT_SUCCESS);
}

int	heredoc(char *limiter, int quoted, t_cmd *cmd)
{
	int		a;
	int		pipes[2];
	pid_t	pid;

	a = -1;
	if (pipe(pipes) < 0)
		return (perror_neg("pipe at heredoc()"));
	pid = fork();
	if (pid < 0)
		return (perror_neg("fork at heredoc()"));
	if (pid == 0)
		call_child(limiter, quoted, pipes, cmd);
	else
	{
		close(pipes[1]);
		waitpid(pid, &a, 0);
		a = dup(pipes[0]);
		close(pipes[0]);
	}
	return (a);
}
