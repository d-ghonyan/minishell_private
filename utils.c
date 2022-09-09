/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/09 18:49:49 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_signaled(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->len)
	{
		j = 0;
		while (cmd[i].fds && j < cmd[i].fds->len)
		{
			if (cmd[i].fds[j].fd == -130)
			{
				*(cmd->status) = 1;
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	not_found(char *exec)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(exec, STDERR_FILENO);
	if (ft_strchr(exec, '/'))
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (NF);
}

int	strcmp_minishell(char *s)
{
	int	i;
	int	j;

	i = ft_strlen(s) - 1;
	j = ft_strlen("minishell") - 1;
	while (i >= 0 && j >= 0 && s[i] == "minishell"[j])
	{
		i--;
		j--;
	}
	if (j == -1 && (i == -1 || s[i] == '/'))
		return (0);
	if (j == -1 || i == -1)
		return (1);
	return (s[i] - "minishell"[j]);
}

int	is_a_builtin(char *s)
{
	return (!ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"));
}

int	check_quotes(char *s)
{
	int		i;
	int		quote;
	char	c;

	quote = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			while (s[++i] && s[i] != c)
				;
			quote = (s[i] == '\0');
		}
		if (!s[i])
			break ;
	}
	if (quote)
		printf(RED "Error: Unclosed quotes\n" RESET);
	return (quote);
}
