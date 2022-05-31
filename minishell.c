#include "minishell.h"

void	die(int signum)
{
	printf(YELLOW "Doing nothing\n" RESET);
	// printf("minishell$ ");
	//exit (EXIT_SUCCESS);
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
			return (NULL);//free_stuff_and_exit(NULL, s, "read() failed at gnl_new()");
		if (a == 0 || c == '\n')
			break ;
		s = ft_strjoin_for_read(s, c);
		if (!s)
			break ;
		//perror_exit_cond("strjoin() failed at gnl_new()", !s);
	}
	return (s);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pipes[2];
	char	*path;
	char	*line;

	//signal(SIGINT, &die);
	//sleep(1);
	signal(SIGQUIT, &die);
	while (1)
	{
		if (pipe(pipes) < 0)
			break ;
		line = readline("minishell$ ");
		add_history(line);
		printf(RED "%s\n" RESET, get_path(line));
	}
}