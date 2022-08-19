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

int	is_in_env(char **env, char *val)
{
	int	i;

	i = 0;
	if (getenv(val))
		return (1);
	while (i < ptr_arr_len(env))
	{
		if (!ft_strcmp(env[i], val))
			return (1);
		i++;
	}
	return (0);
}

char	**env(char **old_env, char *val)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof (*new_env) * (ptr_arr_len(old_env) + 2));
	if (!new_env)
		return (NULL);
	while (i < ptr_arr_len(old_env))
	{
		new_env[i] = ft_strdup((old_env)[i]);
		if (!new_env[i])
		{
			free_ptr_arr(new_env);
			return (NULL);
		}
		i++;
	}
	if (!is_in_env(old_env, val))
		new_env[i++] = ft_strdup(val);
	new_env[i] = NULL;
	free_ptr_arr(old_env);
	return (new_env);
}