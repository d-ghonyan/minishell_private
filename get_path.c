#include "minishell.h"

static char	*free_ret(char **spl);

char	*get_path(char *command)
{
	int		i;
	char	*exec;
	char	*slash;
	char	**spl;

	i = 0;
	spl = ft_split(getenv("PATH"), ':');
	if (!spl)
		return (NULL);
	while (spl[i])
	{
		slash = ft_strjoin(spl[i], "/");
		if (!slash)
			return (NULL);
		exec = ft_strjoin(slash, command);
		free(slash);
		if (!exec)
			return (free_ret(spl));
		if (!access(exec, X_OK))
			return (exec);
		free(exec);
		i++;
	}
	return (NULL);
}

static char	*free_ret(char **spl)
{
	free_ptr_arr(spl);
	return (NULL);
}
