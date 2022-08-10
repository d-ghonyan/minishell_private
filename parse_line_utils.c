#include "minishell.h"

char	*alloc_command(char *line, int i, int size, int j)
{
	char	*s;

	s = malloc(sizeof (*s) * size);
	if (!s)
		return (NULL);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '\'')
				s[j++] = line[i++];
		}
		if (line[i] == '"')
		{
			s[j++] = line[i++];
			while (line[i] && line[i] != '"')
				s[j++] = line[i++];
		}
		s[j++] = line[i++];
	}
	s[j] = '\0';
	return (s);
}
