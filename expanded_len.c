#include "minishell.h"


int	is_a_valid_name(char c, int cond)
{
	if (cond)
		return ((ft_isalpha(c) || c == '_') && c != '$'
			&& c != '\'' && c != '"' && !ft_isspace(c));
	return ((ft_isalnum(c) || c == '_')
		&& c != '$' && c != '\'' && c != '"' && !ft_isspace(c));
}

int	var_len(char *s, int i, int quote)
{
	int		len;

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
	int		j;
	char	*env;
	char	*var;

	j = 0;
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	if (!var)
		return (-1);
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		if (quote && cmd[i] == '"')
			break ;
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = getenv(var);
	free(var);
	return (ft_strlen(env));
}

char	*expanded_env(char *cmd, int i, int quote)
{
	int		j;
	char	*env;
	char	*var;

	j = 0;
	var = malloc(sizeof (*var) * (var_len(cmd, i, quote) + 1));
	if (!var)
		return (NULL);
	while (cmd[i] && is_a_valid_name(cmd[i], i > 0 && cmd[i - 1] == '$'))
	{
		if (quote && cmd[i] == '"')
			break ;
		var[j++] = cmd[i++];
	}
	var[j] = '\0';
	env = getenv(var);
	free(var);
	return (env);
}

char	*strjoin_var(char *s1, char *s2, int j)
{
	int		i;
	int		k;
	char	*s;

	i = -1;
	k = 0;
	s = malloc(sizeof (*s) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	while (++i < j)
		s[i] = s1[i];
	free(s1);
	while (s2 && s2[k])
		s[i++] = s2[k++];
	s[i] = '\0';
	return (s);
}