/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/06 14:41:16 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exp(t_cmd *cmd, char *s, char **res, t_exp *exp);
int		exp_dollar_sign(t_exp *exp, char *res, char *s, int cond);
int		exp_dollar_sign_quote(t_exp *exp, char *res, char *s, int cond);
int		dollar_sign(int *len, int *i, char *s, t_cmd *cmd);
int		dollar_sign_2(int *len, int *i, char *s, t_cmd *cmd);

int	not_a_quote(char c)
{
	return (c != '\'' && c != '"');
}

int	final_len(char *s, t_cmd *cmd, int i, int len)
{
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
				if (dollar_sign(&len, &i, s, cmd))
					;
				else
					len++;
			}
			i += (s[i] != '\0');
		}
		dollar_sign_2(&len, &i, s, cmd);
		len += (s[i] != '\0' && s[i] != '"' && s[i] != '\'' && s[i] != '$');
		i += (s[i] != '\0' && s[i] != '"' && s[i] != '\'' && s[i] != '$');
	}
	return (len);
}

char	*expand_line(char *s, t_cmd *cmd)
{
	t_exp	exp;
	char	*res;

	init_exp(cmd, s, &res, &exp);
	while (s[exp.i])
	{
		if (s[exp.i] == '\'')
		{
			while (s[++exp.i] && s[exp.i] != '\'')
				res[exp.j++] = s[exp.i];
			exp.i += (s[exp.i] != '\0');
		}
		if (s[exp.i] == '"')
		{
			while (s[++exp.i] && s[exp.i] != '"')
				exp_dollar_sign_quote(&exp, res, s, 0);
			exp.i += (s[exp.i] != '\0');
		}
		exp_dollar_sign(&exp, res, s, 1);
		if (s[exp.i] != '\0' && s[exp.i] != '"'
			&& s[exp.i] != '\'' && s[exp.i] != '$')
			res[exp.j++] = s[exp.i++];
	}
	res[exp.j] = '\0';
	return (res);
}
