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

	k = 1;
	i = exec_len(cmd, 0, 0);
	exec->argv = malloc(sizeof (*(exec->argv)) * (argv_count(cmd) + 2));
	if (!exec->argv)
	{
		perror("init_argv() 1: ");
		return ;
	}
	exec->argv[0] = ft_strdup(exec->exec);
	if (!exec->argv[0])
	{
		perror("init_argv() 2: ");
		return ;
	}
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
			{
				perror("init_argv() 3: ");
				return ;
			}
			printf("index %d %d\n", i, argv_len(cmd, i));
			i += argv_len(cmd, i);
			printf("%p %d %c\n", &cmd[i], i, cmd[i] == '\0' ? '+' : '-');
			k++;
		}
	}
	exec->argv[k] = NULL;
}

void	exec_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < cmd->len)
	{
		j = -1;
		init_exec(&(cmd[i].exec), cmd[i].command);
		if (!(cmd[i].exec.exec))
		{
			perror("init_exec(): ");
			return ;
		}
		init_argv(&(cmd[i].exec), cmd[i].command);
		temp = cmd[i].exec.exec;
		cmd[i].exec.exec = expand_line(cmd[i].exec.exec);
		free(temp);
		while (cmd[i].exec.argv[++j])
		{
			temp = cmd[i].exec.argv[j];
			cmd[i].exec.argv[j] = expand_line(cmd[i].exec.argv[j]);
			free(temp);
			printf("%s\n", cmd[i].exec.argv[j]);
		}
		i++;
	}
}
