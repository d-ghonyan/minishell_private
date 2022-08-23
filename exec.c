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

int	init_redirections(t_cmd *cmd, int i, int j)
{
	i = -1;
	while (++i < cmd->len)
	{
		j = -1;
		cmd[i].fds = open_files(cmd[i].command);
		if (!cmd[i].fds && redirection_count(cmd[i].command) > 0)
			return (1);
		while (cmd[i].fds && ++j < cmd[i].fds->len)
		{
			if (cmd[i].fds[j].flags >= 0)
			{
				cmd[i].fds[j].fd = open(cmd[i].fds[j].here,
						cmd[i].fds[j].flags, 0644);
				if (cmd[i].fds[j].fd < 0)
				{
					ft_putstr_fd("open: ", STDERR_FILENO);
					ft_putstr_fd(cmd[i].fds[j].here, STDERR_FILENO);
					perror ("\02");
					break ;
				}
			}
		}
	}
	return (0);
}

void	exec_quotes(char *cmd, t_exec *exec, int *i, int *j)
{
	if (cmd[(*i)] == '\'')
	{
		exec->exec[(*j)++] = cmd[(*i)++];
		while (cmd[(*i)] && cmd[(*i)] != '\'')
			exec->exec[(*j)++] = cmd[(*i)++];
	}
	if (cmd[(*i)] == '"')
	{
		exec->exec[(*j)++] = cmd[(*i)++];
		while (cmd[(*i)] && cmd[(*i)] != '"')
			exec->exec[(*j)++] = cmd[(*i)++];
	}
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
			exec_quotes(cmd, exec, &i, &j);
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
int	init_argv(t_exec *exec, char *cmd, int i, int k)
{
	i = exec_len(cmd, 0, 0);
	exec->argv = malloc(sizeof (*(exec->argv)) * (argv_count(cmd) + 2));
	if (!exec->argv)
		return (perror_ret("init_argv() 1: "));
	exec->argv[0] = ft_strdup(exec->exec);
	if (!exec->argv[0])
		return (perror_ret("init_argv() 2: "));
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
				return (perror_ret("init_argv() 3: "));
			i += argv_len(cmd, i);
			k++;
		}
	}
	exec->argv[k] = NULL;
	return (0);
}

int	exec_argv(t_cmd *cmd, int i, int j)
{
	char	*temp;

	i = -1;
	while (++i < cmd->len)
	{
		j = -1;
		init_exec(&(cmd[i].exec), cmd[i].command);
		if (!(cmd[i].exec.exec))
			return (perror_ret("init_exec()"));
		init_argv(&(cmd[i].exec), cmd[i].command, 0, 1);
		temp = cmd[i].exec.exec;
		cmd[i].exec.exec = expand_line(cmd[i].exec.exec);
		free(temp);
		if (!(cmd[i].exec.exec))
			return (perror_ret("expand_line()"));
		while (cmd[i].exec.argv[++j])
		{
			temp = cmd[i].exec.argv[j];
			cmd[i].exec.argv[j] = expand_line(cmd[i].exec.argv[j]);
			free(temp);
			if (!(cmd[i].exec.argv[j]))
				return (perror_ret("expand_line()"));
		}
	}
	return (init_redirections(cmd, 0, 0));
}
