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

int	main(int argc, char **argv, char **envp)
{
	char	*old_line;
	char	*line;
	t_cmd	*cmd;
	int		a;

	old_line = NULL;
	while (1)
	{
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!old_line || ft_strcmp(line, old_line))
			add_history(line);
		old_line = line;
		if (!line[0] || count_pipes(line) < 0 || check_quotes(line))
		{
			// free(line);
			continue ;
		}
		cmd = parse_line(line);
		exec_argv(cmd);
		// for (int i = 0; i < count_pipes(line) + 1; i++)
		// {
		// 	printf("%s\n", cmd[i].exec.exec);
		// 	for (int j = 0; cmd[i].exec.argv[j]; j++)
		// 		printf("%s ", cmd[i].exec.argv[j]);
		// 	printf("\n");
		// 	// pid_t pid = fork();
		// 	// if (pid == 0)
		// 	// 	execve(get_path(cmd[i].exec.exec), cmd[i].exec.argv, envp);
		// 	// else
		// 	// 	waitpid(pid, &a, 0);
		// }
	}
}

//echo $PATH'asdasdasaaa'aaaaaaaaaaaaaaaaaaaadddddddddddddddddddddddddddddddddd