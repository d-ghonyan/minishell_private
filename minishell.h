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

typedef struct s_exec {
	char	*exec;
	char	**argv;
}	t_exec;

typedef struct s_fds {
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

typedef struct s_cmd {
	int		len;
	int		*status;
	char	*command;
	char	**envp;
	t_fds	*fds;
	t_exec	exec;
}	t_cmd;

int		count_pipes(char *s);
int		init_pipes(int (*pipes)[2], int size, int cond);
int		dup_pipes(int i, int (*pipes)[2], int size);
int		close_pipes(int (*pipes)[2], int size);

int		call_forks(t_cmd *cmd, char *line, int *status);
int		call_builtins(t_cmd *cmd, int i);

int		redirection_index(char *cmd, int i);
int		perror_ret(char *msg);
int		command_not_found(t_cmd *cmd);
int		check_quotes(char *s);
int		is_a_builtin(char *s);
int		exec_argv(t_cmd *cmd);
void	init_signals_parent(void);
void	init_signals_child(void);

void	free_cmd(t_cmd *cmd);
void	free_fds(t_fds *fds);
char	*get_path(char *command);
char	*alloc_command(char *line, int i, int size, int j);
char	*expand_line(char *cmd);
t_cmd	*parse_line(char *line, char **envp);
t_fds	*open_files(char *s);

#endif