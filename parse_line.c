#include "minishell.h"

int	is_a_builtin(char *s)
{
	return (!ft_strcmp(s, "echo")
		|| !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"));
}

void	parse_line(char *line)
{
	int		i;
	char	**commands;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
	}
}
