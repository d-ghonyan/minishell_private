#include "minishell.h"

int	ft_cd(char **argv)
{
	if (ptr_arr_len(argv) > 2)
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ptr_arr_len(argv) == 1)
	{
		if (chdir(getenv("HOME")) < 0)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			perror("");
			return (1);
		}
	}
	else if (chdir(argv[1]) < 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		return (1);
	};
	return (0);
}

int	call_builtins(t_cmd *cmd, int i)
{
	char	*s;

	s = cmd[i].exec.exec;
	if (!ft_strcmp(s, "cd"))
		*(cmd->status) = ft_cd(cmd[i].exec.argv);
}