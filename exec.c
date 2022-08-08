#include "minishell.h"

int	exec_len(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '\'')
		{
			len++;
			while (s[++i] && s[i] != '\'')
				len++;
		}
		if (s[i] == '"')
		{
			len++;
			while (s[++i] && s[i] != '"')
				len++;
		}
		if (!s[i++])
			break ;
		len++;
	}
	return (len);
}

void	init_exec(t_exec *exec, char *cmd)
{
	int		i;
	int		j;

	j = 0;
	i = ft_isspace_index(cmd);
	exec->exec = malloc (sizeof (*cmd) * (exec_len(cmd, 0) + 1));
	while (exec->exec && cmd[i] && !ft_isspace(cmd[i]))
	{
		if (cmd[i] == '\'')
		{
			exec->exec[j++] = cmd[i++];
			while (cmd[i] && cmd[i] != '\'')
				exec->exec[j++] = cmd[i++];
		}
		if (cmd[i] == '"')
		{
			exec->exec[j++] = cmd[i++];
			while (cmd[i] && cmd[i] != '"')
				exec->exec[j++] = cmd[i++];
		}
		if (cmd[i])
			exec->exec[j++] = cmd[i++];
	}
	if (exec->exec)
		exec->exec[j] = '\0';
}

void	exec_argv(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->len)
	{
		init_exec(&(cmd[i].exec), cmd[i].command);
		printf("--%s--\n", cmd[i].exec.exec);
		i++;
	}
}
