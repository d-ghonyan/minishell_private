/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/27 18:50:08 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_ret(char **spl, char *null);

char	*_get_path(char **envp, char *command)
{
	int		i;
	char	*exec;
	char	*slash;
	char	**spl;

	i = -1;
	exec = _getenv(envp, "PATH");
	spl = ft_split(exec, ':');
	free(exec);
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

char	*get_path(t_cmd *cmd, char *command)
{
	char	*ret;
	DIR		*dir;

	dir = opendir(command);
	if (dir)
	{
		stderror_putstr("minishell: ", command, ": is a directory", 1);
		closedir(dir);
	}
	if (!access(command, F_OK))
	{
		ret = ft_strdup(command);
		return (ret);
	}
	return (_get_path(cmd->new_env, command));
}

static char	*free_ret(char **spl, char *null)
{
	free_ptr_arr(spl);
	return (null);
}
