/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/12 14:32:36 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_cmd *cmd, int i, int envp, int single);
int		append_export(char *s);
void	append_env(char **env, char *key, char *value);

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
	int	val;

	if (!s[0] || s[0] == '=' || s[0] == '+')
		return (0);
	i = 0;
	val = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		if (!is_a_valid_name(s[i], i == 0))
			val = 1;
		i++;
	}
	if (val)
		return (0);
	return ((!s[i] || s[i] == '=') || (s[i] == '+' && s[i + 1] == '='));
}

int	ft_strcmp_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if ((s1[i] == '=' && s2[i] == '=') || (!s1[i] && s2[i] == '=')
		|| (s1[i] == '=' && !s2[i]))
		return (s1[i - 1] - s2[i - 1]);
	return (s1[i] - s2[i]);
}

char	**_env(char **old_env, char *val, t_cmd *cmd)
{
	char	*key;
	char	*value;

	if (ft_strchr(val, '='))
	{
		key = _key(val, cmd);
		value = _value(val, cmd);
		if (is_in_env(old_env, key))
		{
			if (append_export(val))
				append_env(cmd->new_env, key, value);
			else
				replace_env(old_env, key, value, cmd);
		}
		else
			old_env = env(old_env, key, value, cmd);
		free(key);
		free(value);
	}
	else
		old_env = env(old_env, val, NULL, cmd);
	return (old_env);
}

int	ft_export(t_cmd *cmd, int i, int single)
{
	int	j;
	int	err;

	j = 0;
	err = 0;
	if (ptr_arr_len(cmd[i].exec.argv) == 1)
		return (ft_env(cmd, i, 0, single));
	while (cmd[i].exec.argv[++j])
	{
		if (!is_valid(cmd[i].exec.argv[j]))
		{
			err = 1;
			stderror_putstr("export: `", cmd[i].exec.argv[j],
				"': not a valid identifier", 1);
		}
		else
			cmd->new_env = _env(cmd->new_env, cmd[i].exec.argv[j], cmd);
	}
	*(cmd->status) = err;
	return (err);
}
