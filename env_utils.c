/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/03 19:21:40 by dghonyan         ###   ########.fr       */
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

char	**copy_env(char **envp, int i)
{
	char	**env;

	env = malloc(sizeof (*env) * (ptr_arr_len(envp)
				+ 1 + !is_in_env(envp, "OLDPWD")));
	perror_exit(NULL, "malloc at copy_env", !env);
	while (envp[++i])
	{
		if (!ft_strcmp_env(envp[i], "OLDPWD"))
			env[i] = ft_strdup("OLDPWD");
		else if (!ft_strcmp_env(envp[i], "PWD"))
			env[i] = ft_strdup_env("PWD", getcwd(NULL, 0));
		else
			env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			free_ptr_arr(env);
			perror_exit(NULL, "malloc at copy_env", 1);
		}
	}
	if (!is_in_env(envp, "OLDPWD"))
		env[i++] = ft_strdup("OLDPWD");
	env[i] = NULL;
	return (env);
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
