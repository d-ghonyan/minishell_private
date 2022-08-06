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

typedef struct s_cmd {
	char	*command;
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;
	char	*here_str;
}	t_cmd;

int		count_pipes(char *s);
int		count_pipes(char *s);
int		command_len(char *s, int i);
void	check_quotes(char *s);
char	*get_path(char *command);
char	*alloc_command(char *line, int i, int size, int j);
t_cmd	*parse_line(char *line);

#endif