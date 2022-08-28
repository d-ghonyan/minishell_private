/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/28 20:31:03 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strcmp_minishell(char *s)
{
	int	i;
	int	j;
	int	len;

	len = 10;
	i = ft_strlen(s);
	j = ft_strlen("minishell");
	i--;
	j--;
	while (i >= 0 && j >= 0 && s[i] == "minishell"[j])
	{
		i--;
		j--;
	}
	if (j == -1 && (s[i] == '/' || i == -1))
		return (0);
	return (s[i] - "minishell"[j]);
}

int	is_a_builtin(char *s)
{
	return (!ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"));
}
