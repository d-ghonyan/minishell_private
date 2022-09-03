/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 19:27:40 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env(char **old_env, char *key, char *value, t_cmd *cmd)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = malloc(sizeof (*new_env)
			* (ptr_arr_len(old_env) + 1 + !is_in_env(old_env, key)));
	perror_exit(cmd, "malloc at env", !new_env);
	while (++i < ptr_arr_len(old_env))
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			free_ptr_arr(new_env);
			if (value)
				free(key);
			perror_exit_free(cmd, value, "malloc at env", 1);
		}
	}
	if (!is_in_env(old_env, key))
		new_env[i++] = ft_strdup_env(key, value);
	new_env[i] = NULL;
	free_ptr_arr(old_env);
	return (new_env);
}

void	replace_env(char **old_env, char *key, char *value)
{
	int	i;
	int	j;

	i = -1;
	j = ptr_arr_len(old_env);
	while (++i < ptr_arr_len(old_env))
	{
		if (!ft_strcmp_env(old_env[i], key))
		{
			free(old_env[i]);
			old_env[i] = ft_strdup_env(key, value);
			if (!old_env[i])
			{
				i = -1;
				while (++i < j)
					free(old_env[i]);
				return ;
			}
		}
	}
}
