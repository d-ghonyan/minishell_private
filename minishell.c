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
	int		status;
	char	*old_line;
	char	*line;
	t_cmd	*cmd;

	old_line = NULL;
	signal(SIGQUIT, &die);
	while (1)
	{
		line = readline(GREEN "minishell" BLUE "$ " RESET);
		if (!old_line || ft_strcmp(line, old_line))
			add_history(line);
		old_line = line;
		check_quotes(line);
		if (count_pipes(line) < 0)
		{
			free(line);
			continue ;
		}
		cmd = parse_line(line);
		exec_argv(cmd);
	}
}
