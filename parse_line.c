#include "minishell.h"

void	ft_echo(char *s)
{
	
}

void	parse_line(char *line)
{
	int		i;
	char	**spl;

	i = 0;
	spl = ft_split(line, ' ');
	if (!spl)
		return ;
	while (spl[i])
	{
		;
	}
}
