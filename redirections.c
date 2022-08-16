#include "minishell.h"

int	redirection_count(char *cmd);

int		init_fds(t_fds *fds, char c1, char c2, char *filename);
t_fds	*alloc_fds(int size);

int	redirection_len(char *cmd, int i, char c)
{
	int	len;

	len = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == c)
			i++;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		while (cmd[i] && !ft_isspace(cmd[i]) && cmd[i] != '<' && cmd[i] != '>')
		{
			len++;
			i++;
		}
		i += (cmd[i] != '\0');
	}
	return (len);
}

char	*get_filename(char *s, int i, char c)
{
	int		j;
	char	*name;

	j = 0;
	name = malloc(sizeof (*name) * (redirection_len(s, i, c) + 1));
	if (!name)
	{
		perror ("malloc at get_filename()");
		return (NULL);
	}
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
	{
		name[j] = s[i];
		j++;
		i++;
	}
	name[j] = '\0';
	return (name);
}

int	redirection_index_but_like_changed(char *cmd, int i)
{
	while (1)
	{
		while (cmd[i] && (cmd[i] == '<' || cmd[i] == '>'))
			i++;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			if (cmd[i] == '\'')
				while (cmd[++i] && cmd[i] != '\'')
					;
			if (cmd[i] == '"')
				while (cmd[++i] && cmd[i] != '"')
					;
			i += (cmd[i] != '\0');
		}
		break ;
	}
	return (i);
}

t_fds	*open_files(char *s)
{
	int		i;
	int		j;
	char	*filename;
	t_fds	*fds;
	
	i = 0;
	j = -1;
	filename = NULL;
	fds = alloc_fds(redirection_count(s));
	while (fds && s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			filename = get_filename(s, i, s[i]);
			if (!filename)
			{
				free_fds(fds);
				return (NULL);
			}
			if (!filename || init_fds(&fds[++j], s[i], s[i + 1], filename))
			{
				return (fds);
			}
			i = redirection_index_but_like_changed(s, i);
		}
		i += (s[i] != '\0');
	}
	return (fds);
}

// int	redirections(t_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < cmd->len)
// 	{
// 		;
// 	}
// }