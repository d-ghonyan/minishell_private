/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/08/31 16:11:43 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
// # define LINUX

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>

# ifdef LINUX
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "readline-dghonyan/include/readline/history.h"
#  include "readline-dghonyan/include/readline/readline.h"
# endif

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
	int		envp_count;
	int		*status;
	char	*line;
	char	*command;
	char	**envp;
	char	**new_env;
	t_fds	*fds;
	t_exec	exec;
}	t_cmd;

int		dir(char *s);
int		has_an_error(t_cmd *cmd, int i);;
int		is_signaled(t_cmd *cmd);
int		has_an_error(t_cmd *cmd, int i);
int		strcmp_minishell(char *s);
int		count_pipes(char *s);
int		init_pipes(int (*pipes)[2], int size, int cond);
int		dup_pipes(t_cmd *cmd, int i, int (*pipes)[2], int size);
int		close_pipes(int (*pipes)[2], int size);
int		is_in_env(char **env, char *key);
int		ft_strcmp_env(char *s1, char *s2);
int		find_index(char *s, char c);
int		children(t_cmd *cmd, int (*pipes)[2], int size, int i);
int		redirection_count(char *cmd);
int		last_fd(t_cmd *cmd, int i, int cond);
int		var_len(char *s, int i, int quote);
int		is_a_valid_name(char c, int cond);
int		expanded_len(char *cmd, int i, int quote, t_cmd *cmd1);
int		call_forks(t_cmd *cmd, char *line, int *status);
int		call_builtins(t_cmd *cmd, int i, int single);
int		heredoc(char *limiter, int quoted, t_cmd *cmd);
int		redirection_index(char *cmd, int i);
int		perror_ret(char *msg);
int		perror_neg(char *msg);
int		check_quotes(char *s);
int		is_a_builtin(char *s);
int		exec_argv(t_cmd *cmd, int i, int j);
int		stderror_putstr(char *s1, char *s2, char *s3, int cond);
int		perror_builtins(char *s1, char *s2, char *s3);
int		init_fds(t_fds *fds, char *s, char *filename, t_cmd *cmd);
void	close_pipes_parent(int len, int (*pipes)[2]);
void	to_from(t_cmd *cmd);
void	not_found(char *exec);
void	perror_exit_free(t_cmd *cmd, char *s, char *msg, int cond);
void	thing(int parent);
void	replace_env(char **old_env, char *key, char *value);
void	remove_env(char **envp, char *key);
void	strjoin_var(char *s1, char *s2);
void	perror_exit(t_cmd *cmd, char *msg, int cond);
void	init_signals_parent(void);
void	init_signals_child(void);
void	init_signals_heredoc(void);
void	free_cmd(t_cmd *cmd);
void	free_fds(t_fds *fds);
char	*_getenv(char **envp, char *s);
char	*ft_strdup_env(char *key, char *value);
char	*_key(char *s);
char	*_value(char *s);
char	*expanded_env(char *cmd, int i, int quote, t_cmd *cmd1);
char	*get_path(t_cmd *cmd, char *command);
char	*alloc_command(char *line, int i, int size, int j);
char	*expand_line(char *cmd, t_cmd *cmd1);
char	**copy_env(char **envp);
char	**env(char **old_env, char *key, char *value, t_cmd *cmd);
char	**_env(char **old_env, char *val, t_cmd *cmd);
t_fds	*open_files(t_cmd *cmd, char *s);
t_cmd	*parse_line(char *line, char **envp);
t_fds	*alloc_fds(int size);

#endif