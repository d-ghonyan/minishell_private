/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/08 13:40:32 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pwds(char *key, char *value, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (!ft_strcmp(key, "PWD"))
	{
		free(cmd->pwd);
		cmd->pwd = ft_strdup(value);
	}
	if (!ft_strcmp(key, "OLDPWD"))
	{
		free(cmd->oldpwd);
		cmd->oldpwd = ft_strdup(value);
	}
}

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
	replace_pwds(key, value, cmd);
	new_env[i] = NULL;
	free_ptr_arr(old_env);
	return (new_env);
}

void	replace_env(char **old_env, char *key, char *value, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = ptr_arr_len(old_env);
	while (++i < j)
	{
		if (!ft_strcmp_env(old_env[i], key))
		{
			replace_pwds(key, value, cmd);
			free(old_env[i]);
			old_env[i] = ft_strdup_env(key, value);
			if (!old_env[i])
			{
				free(key);
				free(value);
				perror_exit(cmd, "malloc at replace_env", 1);
			}
			return ;
		}
	}
}
