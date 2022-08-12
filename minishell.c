#include "minishell.h"

int	empty_event(void)
{

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
	int		a;
	char	*old_line;
	char	*line;
	t_cmd	*cmd;

	cmd = NULL;
	old_line = NULL;
	init_signals_parent();
	rl_event_hook = &empty_event;
	while (1)
	{
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!line)
			return (0);//free stuff
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
			{
				init_signals_child();
				execve(get_path(cmd[i].exec.exec), cmd[i].exec.argv, envp);
			}
			else
				waitpid(pid, &a, 0);
		}
		free_cmd(cmd);
	}
}
