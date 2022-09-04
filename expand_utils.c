/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 18:46:08 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_valid_name(char c, int cond)
{
	if (cond)
		return ((ft_isalpha(c) || c == '_'));
	return ((ft_isalnum(c) || c == '_'));
}

int	var_len(char *s, int i, int quote)
{
	int		len;

	len = 0;
	(void)quote;
	if (s[i] == '?')
		return (1);
	while (s[i] && is_a_valid_name(s[i], i > 0 && s[i - 1] == '$'))
	{
		i++;
		len++;
	}
	return (len);
}

int	expanded_len(char *cmd, int i, int quote, t_cmd *cmd1)
{
	int		j;
	char	*env;
	char	*var;

	j = 0;
	if (cmd[i] == '?')
	{
		var = ft_itoa(*(cmd1->status));
		j = ft_strlen(var);
		free(var);
		return (j);
	}
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	perror_exit(cmd1, "malloc at expanded_len", !var);
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = _getenv(cmd1->new_env, var, cmd1);
	free(var);
	j = ft_strlen(env);
	free(env);
	return (j);
}

char	*expanded_env(char *cmd, int i, int quote, t_cmd *cmd1)
{
	int		j;
	char	*env;
	char	*var;

	j = 0;
	if (cmd[i] == '?')
		return (ft_itoa(*(cmd1->status)));
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	perror_exit(cmd1, "malloc at expanded_env", !var);
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		if (quote && cmd[i] == '"')
			break ;
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = _getenv(cmd1->new_env, var, cmd1);
	free(var);
	return (env);
}

void	strjoin_var(char *s1, char *s2)
{
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = 0;
	while (s2 && s2[j])
	{
		s1[i] = s2[j];
		j++;
		i++;
	}
	free(s2);
}
