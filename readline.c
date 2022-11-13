/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/11 17:21:07 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	ctrl_d(char **new_env, char *pwd, int *status, char *old_line);

int	empty_event(void)
{
	rl_redisplay();
	return (0);
}

void	sigint_p(int signum)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_status = signum + 128;
}

void	_add_history(char *line, char **old_line)
{
	if (line[0] && (!(*old_line) || ft_strcmp(line, *old_line)))
	{
		add_history(line);
		free(*old_line);
		*old_line = ft_strdup(line);
	}
}

void	init_prompt(char **prompt, char *pwd)
{
	char	*temp;

	*prompt = ft_strdup(pwd);
	if (!(*prompt) || !(*prompt)[0])
	{
		free(*prompt);
		*prompt = ft_strdup("minishell$ ");
	}
	else
	{
		temp = *prompt;
		*prompt = ft_strjoin(*prompt, "$ ");
		free(temp);
	}
	temp = *prompt;
	*prompt = ft_strjoin("\001" LIGHTCYAN "\002", *prompt);
	free(temp);
	temp = *prompt;
	*prompt = ft_strjoin(*prompt, "\001" RESET "\002");
	free(temp);
}

int	_readline(char **line, char **new_env, int *status, char *pwd)
{
	int			cond;
	char		*prompt;
	static char	*old_line = NULL;

	init_prompt(&prompt, pwd);
	*line = readline(prompt);
	free(prompt);
	if (!(*line))
		ctrl_d(new_env, pwd, status, old_line);
	_add_history(*line, &old_line);
	cond = (count_pipes(*line) < 0 || check_quotes(*line) || valid_red(*line));
	if (!(*line[0]) || cond)
	{
		*status = (g_status == 130);
		if (cond)
			*status = 258;
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}
