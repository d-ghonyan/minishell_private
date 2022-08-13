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

int	is_a_valid_name(char c, int cond)
{
	if (cond)
		return ((ft_isalpha(c) || c == '_') && c != '$'
			&& c != '\'' && c != '"' && !ft_isspace(c));
	return ((ft_isalnum(c) || c == '_')
		&& c != '$' && c != '\'' && c != '"' && !ft_isspace(c));
}

int	var_len(char *s, int i, int quote)
{
	int		len;

	len = 0;
	while (s[i] && is_a_valid_name(s[i], i > 0 && s[i - 1] == '$'))
	{
		if (quote && s[i] == '"')
			break ;
		i++;
		len++;
	}
	return (len);
}

int	expanded_len(char *cmd, int i, int quote)
{
	int		j;
	char	*env;
	char	*var;

	j = 0;
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	if (!var)
	{
		perror("expanded_len(): ");
		return (-1);
	}
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		if (quote && cmd[i] == '"')
			break ;
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = getenv(var);
	free(var);
	return (ft_strlen(env));
}

char	*expanded_env(char *cmd, int i, int quote)
{
	int		j;
	char	*env;
	char	*var;

	j = 0;
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	if (!var)
	{
		perror("expanded_env(): ");
		return (NULL);
	}
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		if (quote && cmd[i] == '"')
			break ;
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = getenv(var);
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
}
