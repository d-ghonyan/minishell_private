/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/21 15:24:24 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_len(char *cmd, int i, char c)
{
	int	len;

	len = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == c)
			i++;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		while (cmd[i] && !ft_isspace(cmd[i]) && cmd[i] != '<' && cmd[i] != '>')
		{
			len++;
			i++;
		}
		i += (cmd[i] != '\0');
	}
	return (len);
}

char	*get_filename(char *s, int i, char c)
{
	int		j;
	char	*name;

	j = 0;
	name = malloc(sizeof (*name) * (redirection_len(s, i, c) + 1));
	if (!name)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
	{
		name[j] = s[i];
		j++;
		i++;
	}
	name[j] = '\0';
	return (name);
}

int	redirection_index_but_like_changed(char *cmd, int i)
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
		break ;
	}
	return (i);
}

t_fds	*open_files(t_cmd *cmd, char *s, int i, int j)
{
	char	*filename;
	t_fds	*fds;

	fds = alloc_fds(redirection_count(s, 0, 0));
	perror_exit(cmd, "malloc at alloc_fds()", !fds && redirection_count(s, 0, 0));
	while (fds && s[i])
	{
		if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				;
		if (s[i] == '"')
			while (s[++i] && s[i] != '"')
				;
		if (s[i] == '<' || s[i] == '>')
		{
			filename = get_filename(s, i, s[i]);
			perror_exit(cmd, "malloc at get_filename", !filename);
			if (init_fds(fds + ++j, &s[i], filename, cmd))
				return (fds);
			i = redirection_index_but_like_changed(s, i);
		}
		i += (s[i] != '\0');
	}
	return (fds);
}
