#include "minishell.h"

int	ft_cd(char *exec, char **argv)
{

}

int	call_builtins(t_cmd *cmd, int i)
{
	char	*s;

	s = cmd[i].exec.exec;
	if (!ft_strcmp(s, "cd"))
		ft_cd(s, cmd[i].exec.argv);
}