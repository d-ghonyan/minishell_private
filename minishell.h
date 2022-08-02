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
	int		input;
	int		output;
	int		heredoc;
	int		append;
	char	*here_str;
}	t_cmd;

char	*get_path(char *command);
void	parse_line(char *line);

#endif