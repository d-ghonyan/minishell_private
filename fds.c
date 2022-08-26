/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 13:11:44 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flags(char c1, char c2, int *flags)
{
	if (c1 == '>')
	{
		*flags = O_WRONLY | O_CREAT;
		if (c2 == '>')
			*flags = *flags | O_APPEND;
	}
	else if (c1 == '<' && c2 != '<')
	{
		*flags = O_RDONLY;
	}
}

//need to do the heredoc right here
int	init_fds(t_fds *fds, char *c, char *filename, char **envp)
{
	int		flags;
	char	c1;
	char	c2;

	c1 = *c;
	c2 = *(c + 1);
	flags = 0;
	init_flags(c1, c2, &(fds->flags));
	fds->here = filename;
	if (c1 == '>' || (c1 == '<' && c2 != '<'))
	{
		fds->from = (c1 == '<');
		fds->to = (c1 == '>');
	}
	else if (c1 == '<' && c2 == '<')
	{
		fds->flags = -1;
		flags = (ft_strchr(filename, '\'') || ft_strchr(filename, '"'));
		fds->fd = heredoc(filename, flags, envp);
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
	{
		perror ("malloc at open_files()");
		exit(EXIT_FAILURE);
	}
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
