/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/26 13:01:05 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_sign(int *len, int *i, char *s)
{
	if (var_len(s, *i + 1, 1) == 0)
		*len += 1;
	else
	{
		if (expanded_len(s, *i + 1, 1) < 0)
			return (-1);
		*len += expanded_len(s, *i + 1, 1);
	}
	*i += var_len(s, *i + 1, 1);
	return (0);
}

int	final_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				len++;
			i += (s[i] != '\0');
		}
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
			{
				if (s[i] == '$')
				{
					if (var_len(s, i + 1, 1) == 0)
						len += 1;
					else
					{
						if (expanded_len(s, i + 1, 1) < 0)
							return (-1);
						len += expanded_len(s, i + 1, 1);
					}
					i += var_len(s, i + 1, 1);
				}
				else
					len++;
			}
			i += (s[i] != '\0');
		}
		if (s[i] == '$')
		{
			if (var_len(s, i + 1, 0) == 0)
				len += 1;
			else
			{
				if (expanded_len(s, i + 1, 0) < 0)
					return (-1);
				len += expanded_len(s, i + 1, 0);
			}
			i += var_len(s, i + 1, 0) + 1;
		}
		len += (s[i] != '\0' && s[i] != '"' && s[i] != '\'' && s[i] != '$');
		i += (s[i] != '\0' && s[i] != '"' && s[i] != '\'' && s[i] != '$');
	}
	return (len);
}

char	*expand_line(char *s, char **envp)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(*res), (final_len(s) + 1));
	if (!res)
	{
		perror("expand_line(): ");
		return (NULL);
	}
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				res[j++] = s[i];
			i += (s[i] != '\0');
		}
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
			{
				if (s[i] == '$')
				{
					if (var_len(s, i + 1, 1) == 0)
						res[j++] = '$';
					else
					{
						strjoin_var(res, expanded_env(s, i + 1, 1, envp));
						j = ft_strlen(res);
					}
					i += var_len(s, i + 1, 1);
				}
				else
					res[j++] = s[i];
			}
			i += (s[i] != '\0');
		}
		if (s[i] == '$')
		{
			if (var_len(s, i + 1, 0) == 0)
				res[j++] = '$';
			else
			{
				strjoin_var(res, expanded_env(s, i + 1, 0, envp));
				j = ft_strlen(res);
			}
			i += var_len(s, i + 1, 0) + 1;
		}
		if (s[i] != '\0' && s[i] != '"' && s[i] != '\'' && s[i] != '$')
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
