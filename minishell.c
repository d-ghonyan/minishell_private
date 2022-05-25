#include "minishell.h"

void	die(int signum)
{
	printf("HELLOOOOOO");
	exit (EXIT_SUCCESS);
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

int	call_which(char *command, char **envp, int pipes[2])
{
	int		f;
	int		status;
	char	*which;
	char 	**name;

	f = fork();
	if (f < 0)
		;//error
	else if (f == 0)
	{
		if (close(pipes[0]) < 0)
			;//error
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
			;//error
		close(pipes[1]);
		name = ft_split(command, ' ');
		which = ft_strjoin("which ", name[0]);
		free_ptr_arr(name);
		name = ft_split(which, ' ');
		execve("/usr/bin/which", name, envp);
		free_ptr_arr(name);
		free(which);
	}
	else
	{
		close(pipes[1]);
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pipes[2];
	char	*path;
	char	*line;

	signal(SIGINT, &die);
	//sleep(1);
	while (1)
	{
		if (pipe(pipes) < 0)
			break ;
		line = readline("minishell$ ");
		add_history(line);
		if ((status = call_which(line, envp, pipes)))
			;//if (path)
		if (status >= 0)
		{
			path = read_from_pipe(pipes[0]);
			printf("%s\n", path);
		}
		//printf("%s", rl_line_buffer);
		free(line);
		close(pipes[0]);
	}
}