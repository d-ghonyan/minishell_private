#include "minishell.h"

void	check_quotes(char *s)
{
	int	i;
	int	single;
	int	dbl;
	
	single = 0;
	dbl = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			dbl += 1;
			while (s[++i] && s[i] != '"')
				;
			dbl += (s[i] != '\0');
		}
		if (s[i] == '\'')
		{
			single += 1;
			while (s[++i] && s[i] != '\'')
				;
			single += (s[i] != '\0');
		}
		if (!s[i])
			break ;
	}
	if (single % 2 == 1 || dbl % 2 == 1)
		printf(RED "Error\n" RESET);
}