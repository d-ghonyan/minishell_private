/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 12:40:38 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_getenv(char **envp, char *s)
{
	int		i;
	char	*env;

	i = -1;
	env = NULL;
	while (envp[++i])
	{
		if (!ft_strcmp_env(envp[i], s))
		{
			env = _value(envp[i]);
			if (!env)
			{
				perror ("malloc at _getenv()");
				exit (EXIT_FAILURE);
			}
			return (env);
		}
	}
	return (NULL);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	env = malloc(sizeof (*env) * (ptr_arr_len(envp) + 1));
	if (!env)
		return (NULL);
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			free_ptr_arr(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	remove_env(char **envp, char *key)
{
	int		i;
	char	*_key;

	i = 0;
	_key = ft_strjoin(key, "=");
	if (!_key)
	{
		perror("malloc at change_env()");
		return ;
	}
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], _key, ft_strlen(_key)))
		{
			envp[i][0] = '\0';
			break ;
		}
		i++;
	}
	free(_key);
}

int	is_in_env(char **env, char *key)
{
	int	i;

	i = 0;
	while (i < ptr_arr_len(env))
	{
		if (!ft_strcmp_env(env[i], key))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_env(char *key, char *value)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = 0;
	res = malloc(sizeof (*res) * (ft_strlen(key)
		+ ft_strlen(value) + 1 + (value != NULL)));
	if (!res)
		return (NULL);
	while (key[++i])
		res[i] = key[i];
	if (value)
	{
		res[i++] = '=';
		while (value[j])
		{
			res[i] = value[j];
			i++;
			j++;
		}
	}
	res[i] = '\0';
	return (res);
}
