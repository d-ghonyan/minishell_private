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

int	is_valid(char *s);

char	**delete_env(t_cmd *cmd, char **envp, char *del)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	new_env = malloc(sizeof (*new_env) * (ptr_arr_len(envp) + 1));
	perror_exit(cmd, "malloc at delete_env 1", !new_env);
	while (envp[++i])
	{
		if (ft_strcmp_env(envp[i], del))
		{
			new_env[j] = ft_strdup(envp[i]);
			if (!new_env[j])
			{
				free_ptr_arr(new_env);
				perror_exit(cmd, "malloc at delete_env 2", 1);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	free_ptr_arr(envp);
	return (new_env);
}

int	ft_unset(t_cmd *cmd, int k)
{
	int	j;
	int	err;

	j = 0;
	err = 0;
	while (cmd[k].exec.argv[++j])
	{
		if (!is_valid(cmd[k].exec.argv[j]))
		{
			stderror_putstr("export: `", cmd[k].exec.argv[j],
				"': not a valid identifier", 1);
			err = 1;
		}
		else
			cmd->new_env = delete_env(cmd, cmd->new_env, cmd[k].exec.argv[j]);
	}
	*(cmd->status) = err;
	return (err);
}
