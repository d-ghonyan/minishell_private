#include "minishell.h"

int		exec_len(char *s, int i, int cond);
int		redirection_index(char *cmd, int i, char red);
int		argv_len(char *cmd, int i);
int		argv_count(char *cmd);
char	*argv_dup(char *cmd, int i);

void	init_exec(t_exec *exec, char *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = ft_isspace_index(cmd);
	exec->exec = malloc (sizeof (*cmd) * (exec_len(cmd, 0, 1) + 1));
	while (exec->exec && cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			i = redirection_index(cmd, i, cmd[i]);
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
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
		if (!cmd[i] || ((cmd[i] == '<' || cmd[i] == '>'
					|| ft_isspace(cmd[i])) && j))
			break ;
	}
	if (exec->exec)
		exec->exec[j] = '\0';
}

//TODO error handling
void	init_argv(t_exec *exec, char *cmd)
{
	int	i;
	int	k;

	k = 0;
	i = exec_len(cmd, 0, 0);
	exec->argv = malloc(sizeof ((*exec->argv)) * (argv_count(cmd) + 2));
	if (!exec->argv)
		return ;
	exec->argv[k] = ft_strdup(exec->exec);
	if (!exec->argv[k++])
		return ;
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i] == '>' || cmd[i] == '<')
			i = redirection_index(cmd, i, cmd[i]);
		if (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			exec->argv[k] = argv_dup(cmd, i);
			if (!exec->argv[k])
				return ;
			i += argv_len(cmd, i);
			k++;
		}
		if (!cmd[i])
			break ;
	}
	exec->argv[k] = NULL;
}

void	exec_argv(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->len)
	{
		init_exec(&(cmd[i].exec), cmd[i].command);
		init_argv(&(cmd[i].exec), cmd[i].command);
		i++;
	}
}
