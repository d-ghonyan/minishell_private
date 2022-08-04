#include "minishell.h"

static char	*free_ret(char **spl, char **comm, char *null);

char	*_get_path(char *command)
{
	int		i;
	char	*exec;
	char	*slash;
	char	**spl;
	char	**comm;

	i = -1;
	spl = ft_split(getenv("PATH"), ':');
	comm = ft_split(command, ' ');
	if (!spl || !comm)
		return (free_ret(spl, comm, NULL));
	while (spl[++i])
	{
		slash = ft_strjoin(spl[i], "/");
		if (!slash)
			return (free_ret(spl, comm, NULL));
		exec = ft_strjoin(slash, comm[0]);
		free(slash);
		if (!exec)
			return (free_ret(spl, comm, NULL));
		if (!access(exec, X_OK))
			return (free_ret(spl, comm, exec));
		free(exec);
	}
	return (free_ret(spl, comm, NULL));
}

char	*get_path(char *command)
{
	char	**spl;
	char	*ret;

	spl = ft_split(command, ' ');
	if (!spl)
		return (NULL);
	if (!access(spl[0], X_OK))
	{
		ret = ft_strdup(spl[0]);
		free_ptr_arr(spl);
		return (ret);
	}
	free_ptr_arr(spl);
	return (_get_path(command));
}

static char	*free_ret(char **spl, char **comm, char *null)
{
	free_ptr_arr(spl);
	free_ptr_arr(comm);
	return (null);
}
