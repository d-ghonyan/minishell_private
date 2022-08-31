/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/29 19:32:29 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_len(char *s, int i, int cond);
int		argv_len(char *cmd, int i);
int		argv_count(char *cmd, int i, int count);
char	*argv_dup(char *cmd, int i, t_cmd *cmd1, int j);

int	init_redirections(t_cmd *cmd, int i, int j)
{
	i = -1;
	while (++i < cmd->len)
	{
		j = -1;
		cmd[i].fds = open_files(cmd, cmd[i].command);
		if (!cmd[i].fds && redirection_count(cmd[i].command) > 0)
			return (1);
		while (!is_signaled(cmd) && cmd[i].fds && ++j < cmd[i].fds->len)
		{
			if (cmd[i].fds[j].flags >= 0)
			{
				cmd[i].fds[j].fd = open(cmd[i].fds[j].here,
						cmd[i].fds[j].flags, 0644);
				if (cmd[i].fds[j].fd < 0)
				{
					ft_putstr_fd("minishell: ", STDERR_FILENO);
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

int	init_exec(t_exec *exec, char *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = ft_isspace_index(cmd);
	exec->exec = malloc (sizeof (*cmd) * (exec_len(cmd, 0, 1) + 1));
	if (!exec->exec)
		return (1);
	while (cmd[i])
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
	exec->exec[j] = '\0';
	return (0);
}

//TODO error handling
void	init_argv(t_exec *exec, char *cmd, int i, t_cmd *cmd1)
{
	int	k;

	k = 1;
	i = exec_len(cmd, 0, 0);
	exec->argv = malloc(sizeof(*(exec->argv))
			* (argv_count(cmd, exec_len(cmd, 0, 0), 0) + 2));
	perror_exit(cmd1, "malloc at init_argv", !exec->argv);
	exec->argv[0] = ft_strdup(exec->exec);
	perror_exit(cmd1, "malloc at init_argv", !exec->argv[0]);
	while (cmd[i])
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		if (cmd[i] == '>' || cmd[i] == '<')
			i = redirection_index(cmd, i);
		if (cmd[i] && cmd[i] != '<' && cmd[i] != '>' && !ft_isspace(cmd[i]))
		{
			exec->argv[k] = argv_dup(cmd, i, cmd1, 0);
			i += argv_len(cmd, i);
			k++;
		}
	}
	exec->argv[k] = NULL;
}

int	exec_argv(t_cmd *cmd, int i, int j)
{
	char	*temp;

	i = -1;
	while (++i < cmd->len)
	{
		j = -1;
		if (init_exec(&(cmd[i].exec), cmd[i].command))
			perror_exit(cmd, "malloc at init_exec", 1);
		init_argv(&(cmd[i].exec), cmd[i].command, 0, cmd);
		temp = cmd[i].exec.exec;
		cmd[i].exec.exec = expand_line(cmd[i].exec.exec, cmd);
		free(temp);
		if (!(cmd[i].exec.exec))
			perror_exit(cmd, "malloc at expand_line", 1);
		while (cmd[i].exec.argv[++j])
		{
			temp = cmd[i].exec.argv[j];
			cmd[i].exec.argv[j] = expand_line(cmd[i].exec.argv[j], cmd);
			free(temp);
			if (!(cmd[i].exec.argv[j]))
				perror_exit(cmd, "malloc at expand_line", 1);
		}
	}
	return (init_redirections(cmd, 0, 0));
}
