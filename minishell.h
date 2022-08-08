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

typedef struct s_cmd {
	int		len;
	char	*command;
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;
	char	*here_str;
	t_exec	exec;
}	t_cmd;

int		count_pipes(char *s);
int		expanded_len(char *s);
int		var_len(char *s, int i, int quote);
void	check_quotes(char *s);
char	*get_path(char *command);
char	*alloc_command(char *line, int i, int size, int j);
t_cmd	*parse_line(char *line);
t_cmd	*expand_line(t_cmd *cmd);
t_cmd	*init_cmd(int size);
void	exec_argv(t_cmd *cmd);
int		is_a_builtin(char *s);

#endif