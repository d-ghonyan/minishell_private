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

int	exec_len(char *cmd, int i, int cond)
{
	int	len;

	len = 0;
	i = ft_isspace_index(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			i = redirection_index(cmd, i);
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			if (cmd[i] == '\'')
			{
				len++;
				while (cmd[++i] && cmd[i] != '\'')
					len++;
			}
			if (cmd[i] == '"')
			{
				len++;
				while (cmd[++i] && cmd[i] != '"')
					len++;
			}
			i += (cmd[i] != '\0');
			len++;
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

int	argv_count(char *cmd)
{
	int	i;
	int	count;

	i = exec_len(cmd, 0, 0);
	count = 0;
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

char	*argv_dup(char *cmd, int i)
{
	int		j;
	char	*res;

	j = 0;
	res = malloc(sizeof (*res) * (argv_len(cmd, i) + 1));
	if (!res)
	{
		perror("argv_dup(): ");
		return (NULL);
	}
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
