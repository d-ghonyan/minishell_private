/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:53:56 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/10 16:54:11 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	perror_exit_cond(char *errmsg, int cond)
{
	if (cond)
	{
		perror(errmsg);
		exit (EXIT_FAILURE);
	}
}

static char	*ft_strjoin_for_read(char *s, char c)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof (*res) * (ft_strlen(s) + 2));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	free(s);
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

static void	free_stuff_and_exit(char **arr, char *s, char *errmsg)
{
	if (errmsg)
		perror (errmsg);
	if (arr)
		free_ptr_arr(arr);
	free(s);
	exit (EXIT_FAILURE);
}

///TODO change later to return newline too
char	*get_next_line_new(int fd)
{
	char	*s;
	char	c;
	int		a;
	int		not_a_newline;

	not_a_newline = 0;
	s = NULL;
	c = 0;
	a = 0;
	while (1)
	{
		a = read(fd, &c, 1);
		if (a == -1)
			free_stuff_and_exit(NULL, s, "read() failed at gnl_new()");
		if (c != '\n')
			not_a_newline = 1;
		if (a == 0 || (not_a_newline && c == '\n'))
			return (s);
		if (c == '\n')
			continue ;
		s = ft_strjoin_for_read(s, c);
		perror_exit_cond("strjoin() failed at gnl_new()", !s);
	}
	return (NULL);
}
