/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 12:28:11 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_expand(char *s, int i, int j, t_cmd *cmd);

int	here_final_len(char *s, t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (var_len(s, i + 1, 0) == 0)
				len += 1;
			else
			{
				if (expanded_len(s, i + 1, 0, cmd) < 0)
					return (-1);
				len += expanded_len(s, i + 1, 0, cmd);
			}
			i += var_len(s, i + 1, 0) + 1;
		}
		len += (s[i] != '\0' && s[i] != '$');
		i += (s[i] != '\0' && s[i] != '$');
	}
	return (len);
}

int	limiter_quotes(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				len++;
		}
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
				len++;
		}
		i += (s[i] == '"' || s[i] == '\'');
		if (!s[i])
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*final_limiter(char *s, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(sizeof (*res) * (limiter_quotes(s) + 1));
	perror_exit(cmd, "malloc at final_limiter", !res);
	while (s[i])
	{
		if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				res[j++] = s[i];
		if (s[i] == '"')
			while (s[++i] && s[i] != '"')
				res[j++] = s[i];
		i += (s[i] == '"' || s[i] == '\'');
		if (s[i])
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	exit_heredoc(char *line, char *limiter, int pipes[2])
{
	(void)limiter;
	if (!line)
		printf("\b\bwarning: heredoc terminated by EOF\n");
	free(line);
	close(pipes[1]);
	exit (EXIT_SUCCESS);
}

void	here_child(char *limiter, int quoted, int pipes[2], t_cmd *cmd)
{
	char	*line;
	char	*env;

	init_signals_heredoc();
	close(pipes[0]);
	while (1)
	{
		line = readline(MAGENTA "> " RESET);
		if (!line || !ft_strcmp(line, limiter))
			exit_heredoc(line, limiter, pipes);
		if (!quoted && ft_strchr(line, '$'))
		{
			env = here_expand(line, 0, 0, cmd);
			ft_putendl_fd(env, pipes[1]);
			free(env);
		}
		else
			ft_putendl_fd(line, pipes[1]);
		free(line);
	}
	close(pipes[1]);
}
