/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/09 18:48:28 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_command(char *line, int i, int size, int j)
{
	char	*s;

	s = malloc(sizeof (*s) * size);
	if (!s)
		return (NULL);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '\'')
				s[j++] = line[i++];
		}
		if (line[i] == '"')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '"')
				s[j++] = line[i++];
		}
		s[j++] = line[i++];
	}
	s[j] = '\0';
	return (s);
}

int	command_len(char *s, int i)
{
	int	len;

	len = i;
	while (s[i] && s[i] != '|')
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				;
		}
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
				;
		}
		i += (s[i] != '\0');
	}
	return (i - len);
}

t_cmd	*init_cmd(int size, char **envp, char *line)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	(void)line;
	cmd = malloc(sizeof (*cmd) * size);
	if (!cmd)
		return (NULL);
	while (++i < size)
	{
		cmd[i].envp_count = ptr_arr_len(envp);
		cmd[i].fds = NULL;
		cmd[i].envp = envp;
		cmd[i].len = size;
		cmd[i].command = NULL;
		cmd[i].fds = NULL;
		cmd[i].exec.exec = NULL;
		cmd[i].exec.argv = NULL;
		cmd[i].new_env = NULL;
		cmd[i].line = NULL;
		cmd[i].oldpwd = NULL;
	}
	return (cmd);
}

t_cmd	*parse_line(char *line, char **envp)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	cmd = init_cmd(count_pipes(line) + 1, envp, line);
	perror_exit_free(cmd, line, "malloc at parse_line", !cmd);
	i = 0;
	j = 0;
	while (line[i])
	{
		cmd[j].command = alloc_command(line, i, command_len(line, i) + 1, 0);
		perror_exit_free(cmd, line, "malloc at parse_line", !cmd[j].command);
		i += command_len(line, i);
		i += (line[i] != '\0');
		j++;
	}
	return (cmd);
}
