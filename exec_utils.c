/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/09 18:45:24 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_index(char *cmd, int i)
{
	while (1)
	{
		while (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
			i++;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			if (cmd[i] == '\'')
				while (cmd[++i] && cmd[i] != '\'')
					;
			if (cmd[i] == '"')
				while (cmd[++i] && cmd[i] != '"')
					;
			i += (cmd[i] != '\0');
		}
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i] != '<' && cmd[i] != '>')
			break ;
	}
	return (i);
}

int	exec_len(char *cmd, int i, int cond, int len)
{
	i = ft_isspace_index(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			i = redirection_index(cmd, i);
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			if (cmd[i] == '\'')
				while (++len && cmd[++i] && cmd[i] != '\'')
					;
			if (cmd[i] == '"')
				while (++len && cmd[++i] && cmd[i] != '"')
					;
			len += (cmd[i] != '\0');
			i += (cmd[i] != '\0');
		}
		if (!cmd[i] || ((cmd[i] == '<' || cmd[i] == '>'
					|| ft_isspace(cmd[i])) && len))
			break ;
	}
	if (cond)
		return (len);
	return (i);
}

int	argv_len(char *cmd, int i)
{
	int	len;

	len = i;
	while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
	{
		if (cmd[i] == '\'')
		{
			while (cmd[++i] && cmd[i] != '\'')
				;
		}
		if (cmd[i] == '"')
		{
			while (cmd[++i] && cmd[i] != '"')
				;
		}
		i += (cmd[i] != '\0');
	}
	return (i - len);
}

int	argv_count(char *cmd, int i, int count)
{
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i] == '<' || cmd[i] == '>')
			i = redirection_index(cmd, i);
		if (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			count++;
			while (cmd[i] && cmd[i] != '<'
				&& cmd[i] != '>' && !ft_isspace(cmd[i]))
			{
				if (cmd[i] == '\'')
					while (cmd[++i] && cmd[i] != '\'')
						;
				if (cmd[i] == '"')
					while (cmd[++i] && cmd[i] != '"')
						;
				i += (cmd[i] != '\0');
			}
		}
		if (!cmd[i])
			break ;
	}
	return (count);
}

char	*argv_dup(char *cmd, int i, t_cmd *cmd1, int j)
{
	char	*res;

	res = malloc(sizeof (*res) * (argv_len(cmd, i) + 1));
	perror_exit(cmd1, "malloc at argv_dup", !res);
	while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
	{
		if (cmd[i] == '\'')
		{
			res[j++] = cmd[i++];
			while (cmd[i] && cmd[i] != '\'')
				res[j++] = cmd[i++];
		}
		if (cmd[i] == '"')
		{
			res[j++] = cmd[i++];
			while (cmd[i] && cmd[i] != '"')
				res[j++] = cmd[i++];
		}
		if (cmd[i])
			res[j++] = cmd[i++];
	}
	res[j] = '\0';
	return (res);
}
