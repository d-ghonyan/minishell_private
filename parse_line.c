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
	t_cmd	*cmd;

	cmd = malloc(sizeof (*cmd) * size);
	if (!cmd)
		return (NULL);
	cmd->append = 0;
	cmd->here_str = NULL;
	cmd->heredoc = NULL;
	cmd->command = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
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
