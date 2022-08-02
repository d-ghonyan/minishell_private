#include "minishell.h"

static char	*free_ret(char **spl, char **comm, char *null);

char	*get_path(char *command)
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

static char	*free_ret(char **spl, char **comm, char *null)
{
	free_ptr_arr(spl);
	free_ptr_arr(comm);
	return (null);
}
