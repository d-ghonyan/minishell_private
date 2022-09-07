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

void	append_env(char **env, char *key, char *value)
{
	int		i;
	char	*temp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strcmp_env(env[i], key))
		{
			temp = env[i];
			env[i] = ft_strjoin(env[i], value);
			free(temp);
			return ;
		}
	}
}

int	append_export(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	export_print(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		write(1, s + i, fd);
		i++;
	}
	if (s[i])
	{
		write(1, s + i++, fd);
		write(1, "\"", fd);
		while (s[i])
		{
			write(1, s + i, fd);
			i++;
		}
		write(1, "\"", fd);
	}
}

char	*_key(char *s, t_cmd *cmd)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof (*res) * (find_index(s, '=') + 1));
	perror_exit(cmd, "malloc at _value", !res);
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*_value(char *s, t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	*res;

	j = ft_strlen(s) - find_index(s, '=');
	i = find_index(s, '=') + 1;
	if (i > ft_strlen(s))
		i = ft_strlen(s);
	res = malloc(sizeof (*res) * (j + (j == 0)));
	perror_exit(cmd, "malloc at _value", !res);
	j = 0;
	while (s[i])
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
