#include "minishell.h"

int	after_pipe(char *s, int i)
{
	while (s[i] && s[i] != '|')
	{
		if (!ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	before_pipe(char *s, int i)
{
	if (i <= 0)
		return (0);
	while (i)
	{
		if (!ft_isspace(s[i - 1]))
			return (1);
		i--;
	}
	return (0);
}

int	count_pipes(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"')
			while (s[++i] && s[i] != '"')
				;
		if (s[i] == '\'')
			while (s[++i] && s[i] != '\'')
				;
		if (s[i] == '|')
		{
			count++;
			if (!after_pipe(s, i + 1) || s[i + 1] == '|' || !before_pipe(s, i))
			{
				printf("Syntax error near %d\n", i);
				return (-1);
			}
		}
		i += (s[i] != '\0');
	}
	return (count);
}