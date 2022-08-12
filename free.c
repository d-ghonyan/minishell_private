#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = -1;
	len = cmd->len;
	while (++i < len)
	{
		free(cmd[i].here_str);
		free(cmd[i].heredoc);
		free(cmd[i].infile);
		free(cmd[i].outfile);
		free(cmd[i].command);
		free(cmd[i].exec.exec);
		free_ptr_arr(cmd[i].exec.argv);
	}
	free(cmd);
}
