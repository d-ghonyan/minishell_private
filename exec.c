/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_len(char *s, int i, int cond);
int		argv_len(char *cmd, int i);
int		argv_count(char *cmd);
char	*argv_dup(char *cmd, int i);

int	init_redirections(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->len)
	{
		cmd[i].fds = open_files(cmd[i].command);
		if (!cmd[i].fds)
			return (1);
	}
	return (0);
}

void	init_exec(t_exec *exec, char *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = ft_isspace_index(cmd);
	exec->exec = malloc (sizeof (*cmd) * (exec_len(cmd, 0, 1) + 1));
	while (exec->exec && cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			i = redirection_index(cmd, i);
		while (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			if (cmd[i] == '\'')
			{
				exec->exec[j++] = cmd[i++];
				while (cmd[i] && cmd[i] != '\'')
					exec->exec[j++] = cmd[i++];
			}
			if (cmd[i] == '"')
			{
				exec->exec[j++] = cmd[i++];
				while (cmd[i] && cmd[i] != '"')
					exec->exec[j++] = cmd[i++];
			}
			if (cmd[i])
				exec->exec[j++] = cmd[i++];
		}
		if (!cmd[i] || ((cmd[i] == '<' || cmd[i] == '>'
					|| ft_isspace(cmd[i])) && j))
			break ;
	}
	if (exec->exec)
		exec->exec[j] = '\0';
}

//TODO error handling
void	init_argv(t_exec *exec, char *cmd)
{
	int	i;
	int	k;

	k = 1;
	i = exec_len(cmd, 0, 0);
	exec->argv = malloc(sizeof (*(exec->argv)) * (argv_count(cmd) + 2));
	if (!exec->argv)
	{
		perror("init_argv() 1: ");
		return ;
	}
	exec->argv[0] = ft_strdup(exec->exec);
	if (!exec->argv[0])
	{
		perror("init_argv() 2: ");
		return ;
	}
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i] == '>' || cmd[i] == '<')
			i = redirection_index(cmd, i);
		if (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			exec->argv[k] = argv_dup(cmd, i);
			if (!exec->argv[k])
			{
				perror("init_argv() 3: ");
				return ;
			}
			i += argv_len(cmd, i);
			k++;
		}
	}
	exec->argv[k] = NULL;
}

int	exec_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < cmd->len)
	{
		j = -1;
		init_exec(&(cmd[i].exec), cmd[i].command);
		if (!(cmd[i].exec.exec))
		{
			perror("init_exec()");
			return (1);
		}
		init_argv(&(cmd[i].exec), cmd[i].command);
		temp = cmd[i].exec.exec;
		cmd[i].exec.exec = expand_line(cmd[i].exec.exec);
		free(temp);
		if (!(cmd[i].exec.exec))
		{
			perror("expand_line()");
			return (1);
		}
		while (cmd[i].exec.argv[++j])
		{
			temp = cmd[i].exec.argv[j];
			cmd[i].exec.argv[j] = expand_line(cmd[i].exec.argv[j]);
			free(temp);
			if (!(cmd[i].exec.argv[j]))
			{
				perror("expand_line()");
				return (1);
			}
		}
	}
	return (init_redirections(cmd));
}
