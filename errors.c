#include "minishell.h"

int	perror_ret(char *msg)
{
	perror(msg);
	return (1);
}