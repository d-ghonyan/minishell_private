#include "minishell.h"

int	redirection_count(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] == '>' || cmd[i] == '<')
		{
			while (cmd[i] && cmd[i] == '>' || cmd[i] == '<')
				i++;
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			if (cmd[i] && !ft_isspace(cmd[i])
				&& cmd[i] != '<' && cmd[i] != '>')
			{
				count++;
				while (cmd[i] && !ft_isspace(cmd[i])
					&& cmd[i] != '<' && cmd[i] != '>')
					i++;
			}
		}
		i += (cmd[i] != '\0');
	}
	return (count);
}
