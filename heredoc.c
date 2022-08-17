#include "minishell.h"

char	*final_limiter(char *s);
int		here_final_len(char *s);
int		limiter_quotes(char *s);
void	here_child(char *limiter, int quoted, int pipes[2]);

char	*here_expand(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(*res), (here_final_len(s) + 1));
	if (!res)
	{
		perror("malloc at here_expand(): ");
		return (NULL);
	}
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (var_len(s, i + 1, 0) == 0)
				res[j++] = '$';
			else
			{
				strjoin_var(res, expanded_env(s, i + 1, 0));
				j = ft_strlen(res);
			}
			i += var_len(s, i + 1, 0) + 1;
		}
		if (s[i] != '\0' && s[i] != '$')
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

//should expand variables when quoted is false
int	heredoc(char *limiter, int quoted)
{
	int		a;
	int		pipes[2];
	char	*l;
	pid_t	pid;

	a = -1;
	if (pipe(pipes) < 0)
		return (perror_neg("pipe at heredoc()"));
	pid = fork();
	if (pid < 0)
		return (perror_neg("fork at heredoc()"));
	if (pid == 0)
	{
		l = final_limiter(limiter);
		if (!l)
		{
			perror("malloc at heredoc()");
			exit (EXIT_FAILURE);
		}
		here_child(l, quoted, pipes);
		free(l);
		exit (EXIT_SUCCESS);
	}
	else
	{
		close(pipes[1]);
		waitpid(pid, &a, 0);
		a = dup(pipes[0]);
		close(pipes[0]);
	}
	return (a);
}
