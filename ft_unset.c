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

char	**delete_env(char **envp, char *del)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	j = 0;
	new_env = malloc(sizeof (*new_env) * ptr_arr_len(envp));
	if (!new_env)
	{
		perror("malloc at delete_env");
		exit(EXIT_FAILURE);
	}
	while (envp[++i])
	{
		if (ft_strcmp_env(envp[i], del))
		{
			new_env[j++] = ft_strdup(envp[i]);
			if (!new_env[j])
			{
				perror("malloc at delete_env");
				exit(EXIT_FAILURE);
			}
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
			cmd->new_env = delete_env(cmd->new_env, cmd[k].exec.argv[j]);
	}
	*(cmd->status) = err;
	return (0);
}
