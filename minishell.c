#include "minishell.h"

void	die(int signum)
{
	printf(YELLOW "Doing nothing\n" RESET);
}

static char	*ft_strjoin_for_read(char *s, char c)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof (*res) * (ft_strlen(s) + 2));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s))
	{
		res[i] = s[i];
		i++;
	}
	free(s);
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

char	*read_from_pipe(int pipe)
{
	char	*s;
	char	c;
	int		a;

	s = NULL;
	c = 0;
	a = 0;
	while (1)
	{
		a = read(pipe, &c, 1);
		if (a == -1)
			return (NULL);
		if (a == 0)
			break ;
		s = ft_strjoin_for_read(s, c);
		if (!s)
			break ;
	}
	return (s);
}

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

int	main(int argc, char **argv, char **envp)
{
	int		a;
	char	*old_line;
	char	*line;
	t_cmd	*cmd;

	old_line = NULL;
	while (1)
	{
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
			continue ;
		if (line[0] && (!old_line || ft_strcmp(line, old_line)))
			add_history(line);
		old_line = line;
		cmd = parse_line(line);
		exec_argv(cmd);
		for (int i = 0; i < count_pipes(line) + 1; i++)
		{
			pid_t pid = fork();
			if (pid == 0)
				execve(get_path(cmd[i].exec.exec), cmd[i].exec.argv, envp);
			else
				waitpid(pid, &a, 0);
		}
		free_cmd(cmd);
		// for (int i = 0; i < cmd->len; i++)
		// {
		// 	for (int j = 0; cmd[i].exec.argv[j]; j++)
		// 	{
		// 		printf("%s\n", cmd[i].exec.argv[j]);
		// 	}
		// }
	}
}

//echo $PATH'asdasdasaaa'aaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddddd