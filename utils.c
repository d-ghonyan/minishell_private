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

void	not_found(char *exec)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(exec, STDERR_FILENO);
	if (ft_strchr(exec, '/'))
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

int	strcmp_minishell(char *s)
{
	int	i;
	int	j;

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
