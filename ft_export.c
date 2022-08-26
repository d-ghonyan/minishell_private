/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 13:41:47 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_index(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!is_a_valid_name(s[i], i == 0))
			return (0);
		i++;
	}
	return (s[0] != '=');
}

int	ft_strcmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1 != s2)
		i++;
	if ((s1[i] == '=' && s2[i] == '=') || (!s1[i] && s2[i] == '=')
		|| (s1[i] == '=' && !s2[i]))
		return (s1[i - 1] - s2[i - 1]);
	return (s1[i] - s2[i]);
}

char	**_env(char **old_env, char *val, char **envp)
{
	char	*key;
	char	*value;

	if (ft_strchr(val, '='))
	{
		key = _key(val);
		value = _value(val);
		if (is_in_env(old_env, key))
			replace_env(old_env, key, value);
		else
			old_env = env(old_env, key, value);
		free(key);
		free(value);
	}
	else
		old_env = env(old_env, val, NULL);
	return (old_env);
}

int	ft_export(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	if (ptr_arr_len(cmd[i].exec.argv) == 1)
		return (0);
	while (cmd[i].exec.argv[++j])
	{
		if (!is_valid(cmd[i].exec.argv[j]))
			stderror_putstr("export: `", cmd[i].exec.argv[j],
				"': not a valid identifier", 1);
		else
			cmd->new_env = _env(cmd->new_env, cmd[i].exec.argv[j], cmd->envp);
	}
	return (0);
}
