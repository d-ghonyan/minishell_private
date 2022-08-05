/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:56:10 by dghonyan          #+#    #+#             */
/*   Updated: 2022/04/09 17:56:12 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

// static int	has_nl(char *s, int i)
// {
// 	while (s[i] && s[i] != '\n')
// 		i++;
// 	if (s[i] == '\n')
// 		return (1);
// 	return (0);
// }

// static int	line_len(char *s, int i)
// {
// 	int	len;

// 	len = 0;
// 	while (s[i] && s[i] != '\n')
// 	{
// 		i++;
// 		len++;
// 	}
// 	if (s[i] == '\n')
// 		return (len + 1);
// 	return (len);
// }

// static char	*get_line(char *s, int *i)
// {
// 	int		a;
// 	char	*line;

// 	line = (char *)malloc(sizeof (*line) * (line_len(s, *i) + 1));
// 	if (!line)
// 	{
// 		free((void *)s);
// 		return (NULL);
// 	}
// 	a = 0;
// 	while (s[*i] && s[*i] != '\n')
// 	{
// 		line[a] = s[*i];
// 		a++;
// 		*i += 1;
// 	}
// 	if (s[*i] == '\n')
// 	{
// 		line[a++] = '\n';
// 		*i += 1;
// 	}
// 	line[a] = '\0';
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*s[FOPEN_MAX];
// 	//static char	*s = NULL;
// 	static int	i = 0;
// 	char		temp[BUFFER_SIZE + 1];
// 	int			a;

// 	if (fd < 0 || BUFFER_SIZE < 1)
// 		return (NULL);
// 	a = 1;
// 	while (a != 0)
// 	{
// 		a = read(fd, temp, BUFFER_SIZE);
// 		if (a == -1 || (a == 0 && (!s[fd] || s[fd][i] == '\0')))
// 		{
// 			free((void *)(s[fd]));
// 			i = 0;
// 			return (NULL);
// 		}
// 		temp[a] = '\0';
// 		s[fd] = ft_strjoin_gnl(s[fd], temp);
// 		if (!s[fd])
// 			return (NULL);
// 		if (has_nl(s[fd], i) || s[fd][i] == '\0')
// 			break ;
// 	}
// 	return (get_line(s[fd], &i));
// }
