/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 12:05:32 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_fd(t_cmd *cmd, int i, int cond)
{
	int	to;
	int	from;
	int	j;

	j = -1;
	to = -1;
	from = -1;
	if (!cmd[i].fds)
		return (-1);
	while (++j < cmd[i].fds->len)
	{
		if (cmd[i].fds[j].to)
			to = cmd[i].fds[j].fd;
		if (cmd[i].fds[j].from || cmd[i].fds[j].flags < 0)
			from = cmd[i].fds[j].fd;
	}
	if (cond)
		return (to);
	return (from);
}

void	init_flags(char c1, char c2, int *flags)
{
	if (c1 == '>')
	{
		*flags = O_WRONLY | O_CREAT | O_CLOEXEC;
		if (c2 == '>')
			*flags = *flags | O_APPEND;
		else
			*flags = *flags | O_TRUNC;
	}
	else if (c1 == '<' && c2 != '<')
	{
		*flags = O_RDONLY;
	}
}

int	init_fds(t_fds *fds, char *c, char *filename, t_cmd *cmd)
{
	char	c1;
	char	c2;

	c1 = *c;
	c2 = *(c + 1);
	init_flags(c1, c2, &(fds->flags));
	if (c1 == '>' || (c1 == '<' && c2 != '<'))
	{
		fds->from = (c1 == '<');
		fds->to = (c1 == '>');
		fds->here = expand_line(filename, cmd);
		free(filename);
	}
	else if (c1 == '<' && c2 == '<')
	{
		fds->flags = -1;
		fds->quoted = (ft_strchr(filename, '\'') || ft_strchr(filename, '"'));
		fds->fd = heredoc(filename, fds->quoted, cmd);
		fds->here = filename;
		return (fds->fd == -130);
	}
	return (0);
}

t_fds	*alloc_fds(int size)
{
	int		i;
	t_fds	*fds;

	i = -1;
	if (size <= 0)
		return (NULL);
	fds = malloc (sizeof (*fds) * size);
	if (!fds)
		return (NULL);
	while (++i < size)
	{
		fds[i].append = 0;
		fds[i].fd = -1;
		fds[i].flags = -1;
		fds[i].from = 0;
		fds[i].here = NULL;
		fds[i].heredoc = 0;
		fds[i].len = size;
		fds[i].quoted = 0;
		fds[i].to = 0;
	}
	return (fds);
}
