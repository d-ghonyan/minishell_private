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

static char	*free_ret(char **spl, char *null);

char	*_get_path(char *command)
{
	int		i;
	char	*exec;
	char	*slash;
	char	**spl;

	i = -1;
	spl = ft_split(getenv("PATH"), ':');
	if (!spl)
		return (NULL);
	while (spl[++i])
	{
		slash = ft_strjoin(spl[i], "/");
		if (!slash)
			return (free_ret(spl, NULL));
		exec = ft_strjoin(slash, command);
		free(slash);
		if (!exec)
			return (free_ret(spl, NULL));
		if (!access(exec, F_OK))
			return (free_ret(spl, exec));
		free(exec);
	}
	return (free_ret(spl, NULL));
}

char	*get_path(char *command)
{
	char	*ret;

	if (!access(command, F_OK))
	{
		ret = ft_strdup(command);
		return (ret);
	}
	return (_get_path(command));
}

static char	*free_ret(char **spl, char *null)
{
	free_ptr_arr(spl);
	return (null);
}
