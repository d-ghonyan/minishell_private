#include "minishell.h"

int	command_len(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != '|')
	{
		if (s[i] == '\'')
		{
			i++;
			len++;
			while (s[i] && s[i] != '\'')
			{
				i++;
				len++;
			}
		}
		if (s[i] == '"')
		{
			i++;
			len++;
			while (s[i] && s[i] != '"')
			{
				i++;
				len++;
			}
		}
		if (!s[i] || s[i] == '|')
			break ;
		i++;
		len++;
	}
	return (len);
}

t_cmd	*init_cmd(int size)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	cmd = malloc(sizeof (*cmd) * size);
	if (!cmd)
		return (NULL);
	while (++i < size)
	{
		cmd[i].len = size;
		cmd[i].append = 0;
		cmd[i].here_str = NULL;
		cmd[i].heredoc = NULL;
		cmd[i].command = NULL;
		cmd[i].infile = NULL;
		cmd[i].outfile = NULL;
		cmd[i].exec.exec = NULL;
		cmd[i].exec.argv = NULL;
	}
	return (cmd);
}

void	*free_cmd(t_cmd *cmd)
{
	free(cmd);
	return (NULL);
}

t_cmd	*parse_line(char *line)
{
	int		i;
	int		j;
	int		k;
	char	**commands;
	t_cmd	*cmd;

	i = count_pipes(line);
	if (i < 0)
		return (NULL);
	cmd = init_cmd(i + 1);
	if (!cmd)
	{
		perror("Malloc failed at parse_line: ");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (line[i])
	{
		cmd[j++].command = alloc_command(line, i, command_len(line, i) + 1, 0);
		i += command_len(line, i);
		i += (line[i] != '\0');
	}
	return (cmd);
}
