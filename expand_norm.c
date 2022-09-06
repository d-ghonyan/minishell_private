/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:07:17 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/06 14:40:10 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	final_len(char *s, t_cmd *cmd, int i, int len);
int	not_a_quote(char c);

void	init_exp(t_cmd *cmd, char *s, char **res, t_exp *exp)
{
	*res = ft_calloc(sizeof(**res), (final_len(s, cmd, 0, 0) + 1));
	perror_exit(cmd, "malloc at expand_line", !(*res));
	exp->s = s;
	exp->cmd = cmd;
	exp->i = 0;
	exp->j = 0;
}

int	exp_dollar_sign_quote(t_exp *exp, char *res, char *s, int cond)
{
	int	i;

	i = exp->i;
	if (s[exp->i] == '$')
	{
		if (var_len(s, exp->i + 1, 1) == 0)
			res[exp->j++] = '$';
		else
		{
			strjoin_var(res, expanded_env(s, exp->i + 1, 1, exp->cmd));
			exp->j = ft_strlen(res);
		}
		exp->i += var_len(s, exp->i + 1, 1);
		return (1);
	}
	else if (s[i] != '$' && !cond)
		res[exp->j++] = s[exp->i];
	return (0);
}

int	exp_dollar_sign(t_exp *exp, char *res, char *s, int cond)
{
	int	i;

	i = exp->i;
	if (s[exp->i] == '$')
	{
		if (var_len(s, exp->i + 1, 1) == 0 && not_a_quote(s[exp->i + 1]))
			res[exp->j++] = '$';
		else
		{
			strjoin_var(res, expanded_env(s, exp->i + 1, 1, exp->cmd));
			exp->j = ft_strlen(res);
		}
		exp->i += var_len(s, exp->i + 1, 1) + 1;
		return (1);
	}
	else if (s[i] != '$' && !cond)
		res[exp->j++] = s[exp->i];
	return (0);
}

int	dollar_sign(int *len, int *i, char *s, t_cmd *cmd)
{
	if (s[*i] == '$')
	{
		if (var_len(s, *i + 1, 1) == 0)
			*len += 1;
		else
		{
			if (expanded_len(s, *i + 1, 1, cmd) < 0)
				return (-1);
			*len += expanded_len(s, *i + 1, 1, cmd);
		}
		*i += var_len(s, *i + 1, 1);
		return (1);
	}
	return (0);
}

int	dollar_sign_2(int *len, int *i, char *s, t_cmd *cmd)
{
	if (s[*i] == '$')
	{
		if (var_len(s, *i + 1, 0) == 0 && not_a_quote(s[*i + 1]))
			*len += 1;
		else
		{
			if (expanded_len(s, *i + 1, 0, cmd) < 0)
				return (-1);
			*len += expanded_len(s, *i + 1, 0, cmd);
		}
		*i += var_len(s, *i + 1, 0) + 1;
		return (1);
	}
	return (0);
}
