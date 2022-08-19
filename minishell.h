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

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <features.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "colors.h"
# include "libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_exec
{
	char	*exec;
	char	**argv;
}	t_exec;

typedef struct s_fds
{
	int		len;
	int		flags;
	int		fd;
	int		to;
	int		from;
	int		append;
	int		heredoc;
	int		quoted;
	char	*here;
}	t_fds;

typedef struct s_cmd
{
	int		len;
	int		*status;
	char	*command;
	char	**envp;
	char	**new_env;
	t_fds	*fds;
	t_exec	exec;
}	t_cmd;

int		count_pipes(char *s);
int		init_pipes(int (*pipes)[2], int size, int cond);
int		dup_pipes(t_cmd *cmd, int i, int (*pipes)[2], int size);
int		close_pipes(int (*pipes)[2], int size);

char	**env(char **old_env, char *val);

int		children(t_cmd *cmd, int (*pipes)[2], int size, int i);
int		redirection_count(char *cmd);
int		last_fd(t_cmd *cmd, int i, int cond);
int		var_len(char *s, int i, int quote);
int		is_a_valid_name(char c, int cond);
int		expanded_len(char *cmd, int i, int quote);
char	*expanded_env(char *cmd, int i, int quote);
void	strjoin_var(char *s1, char *s2);
int		call_forks(t_cmd *cmd, char *line, int *status);
int		call_builtins(t_cmd *cmd, int i);
int		heredoc(char *limiter, int quoted);
int		redirection_index(char *cmd, int i);
int		perror_ret(char *msg);
int		perror_neg(char *msg);
int		command_not_found(t_cmd *cmd);
int		check_quotes(char *s);
int		is_a_builtin(char *s);
int		exec_argv(t_cmd *cmd, int i, int j);
int		stderror_putstr(char *s1, char *s2, char *s3, int cond);
int		perror_builtins(char *s1, char *s2, char *s3);
void	init_signals_parent(void);
void	init_signals_child(void);
void	init_signals_heredoc(void);
void	free_cmd(t_cmd *cmd);
void	free_fds(t_fds *fds);
char	*get_path(char *command);
char	*alloc_command(char *line, int i, int size, int j);
char	*expand_line(char *cmd);
t_cmd	*parse_line(char *line, char **envp);
t_fds	*open_files(char *s);

#endif