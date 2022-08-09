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
	while (s[i] && is_a_valid_name(s[i], i > 0 && s[i - 1] == '$'))
	{
		if (quote && s[i] == '"')
			break ;
		i++;
		len++;
	}
	return (len);
}

int	expanded_len(char *cmd, int i, int quote)
{
	char	*var;

	var = malloc(sizeof (*var) * (var_len(cmd, i, quote)));
}