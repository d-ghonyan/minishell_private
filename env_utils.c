/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/04 14:14:17 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_getenv(char **envp, char *s, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strcmp_env(envp[i], s))
			return (_value(envp[i], cmd));
	}
	if (!ft_strcmp(s, "PWD"))
		return (ft_strdup(cmd->pwd));
	else if (!ft_strcmp(s, "OLDPWD"))
		return (ft_strdup(cmd->oldpwd));
	return (NULL);
}

char	**copy_env(char **envp, int i, char *cwd)
{
	int		j;
	char	**_env;

	j = 0;
	_env = malloc(sizeof (*_env) * (ptr_arr_len(envp) + 1));
	perror_exit_free(NULL, cwd, "malloc at copy_env", !_env);
	while (envp[++i])
	{
		if (ft_strcmp_env(envp[i], "OLDPWD") && ft_strcmp_env(envp[i], "PWD"))
		{	
			_env[j] = ft_strdup(envp[i]);
			if (!_env[j++])
			{
				free_ptr_arr(_env);
				perror_exit_free(NULL, cwd, "malloc at copy_env loop", 1);
			}
		}
	}
	_env[j] = NULL;
	_env = env(_env, "PWD", cwd, NULL);
	_env = env(_env, "OLDPWD", NULL, NULL);
	return (_env);
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
