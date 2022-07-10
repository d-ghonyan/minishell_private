#include "minishell.h"

static char	*free_ret(char **spl, char *null);

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
			return (free_ret(spl, NULL));
		if (!access(exec, X_OK))
			return (free_ret(spl, exec));
		free(exec);
		i++;
	}
	return (free_ret(spl, NULL));
}

static char	*free_ret(char **spl, char *null)
{
	if (spl)
		free_ptr_arr(spl);
	return (null);
}
