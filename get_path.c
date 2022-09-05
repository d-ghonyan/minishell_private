/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/05 13:02:35 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_ret(char **spl, char *null);

int	dir(char *s)
{
	int		old_errno;
	DIR		*dir;

	old_errno = errno;
	if (!s)
		return (0);
	dir = opendir(s);
	if (dir)
	{
		closedir(dir);
		errno = old_errno;
		return (1);
	}
	errno = old_errno;
	return (0);
}

char	*ft_strdup_free(char *s)
{
	char	*dup;

	if (!s)
		return (ft_strdup("."));
	else if (!s[0])
	{
		dup = ft_strdup(s);
		free(s);
		return (dup);
	}
	else
		return (s);
}

char	*_get_path(char **envp, char *command, t_cmd *cmd)
{
	int		i;
	char	*exec;
	char	*slash;
	char	**spl;

	i = -1;
	exec = _getenv(envp, "PATH", cmd);
	exec = ft_strdup_free(exec);
	spl = ft_split(exec, ':');
	free(exec);
	while (spl && spl[++i])
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

	if (dir(command))
		stderror_putstr("minishell: ", command, ": is a directory", 1);
	if (ft_strchr(command, '/') && !access(command, F_OK))
	{
		ret = ft_strdup(command);
		return (ret);
	}
	else if (ft_strchr(command, '/') && access(command, F_OK))
		return (NULL);
	return (_get_path(cmd->new_env, command, cmd));
}

static char	*free_ret(char **spl, char *null)
{
	free_ptr_arr(spl);
	return (null);
}
