/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 18:34:00 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_not_found(t_cmd *cmd)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (i < cmd->len)
	{
		path = get_path(cmd->new_env, cmd[i].exec.exec);
		if (!path && !is_a_builtin(cmd[i].exec.exec))
			return (i);
		free(path);
		i++;
	}
	return (-1);
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
	cmd = malloc(sizeof (*cmd) * size);
	if (!cmd)
		return (NULL);
	while (++i < size)
	{
		cmd[i].fds = NULL;
		cmd[i].envp = envp;
		cmd[i].len = size;
		cmd[i].command = NULL;
		cmd[i].fds = NULL;
		cmd[i].exec.exec = NULL;
		cmd[i].exec.argv = NULL;
		cmd[i].new_env = NULL;
	}
	return (cmd);
}

//TODO HANDLING
t_cmd	*parse_line(char *line, char **envp)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	cmd = init_cmd(count_pipes(line) + 1, envp, line);
	if (!cmd)
	{
		perror("Malloc failed at parse_line(): ");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (line[i])
	{
		cmd[j].command = alloc_command(line, i, command_len(line, i) + 1, 0);
		if (!cmd[j].command)
		{
			perror("Malloc failed at alloc_command(): ");
			return (NULL);
		}
		i += command_len(line, i);
		i += (line[i] != '\0');
		j++;
	}
	return (cmd);
}
