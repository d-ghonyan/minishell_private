#include "minishell.h"

int	check_quotes(char *s)
{
	int		i;
	int		quote;
	char	c;

	quote = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			while (s[++i] && s[i] != c)
				;
			quote = (s[i] == '\0');
		}
		if (!s[i])
			break ;
	}
	if (quote)
		printf(RED "Error: Unclosed quotes\n" RESET);
	return (quote);
}
