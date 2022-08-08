#include "minishell.h"

int	is_a_valid_name(char c, int cond)
{
	if (cond)
		return ((ft_isalpha(c) || c == '_') && c != '$' && !ft_isspace(c));
	return ((ft_isalnum(c) || c == '_') && c != '$' && !ft_isspace(c));
}

int	var_len(char *s, int i, int quote)
{
	int	len;

	len = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (quote && s[i] == '"')
			break ;
		i++;
		len++;
	}
	return (len);
}