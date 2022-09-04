/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/04 15:03:37 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	sigint_p(int signum)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_status = signum + 128;
}

void	_add_history(char *line)
{
	if (line[0])
		add_history(line);
}

void	init_prompt(char **prompt, char *pwd)
{
	char	*temp;
 
	*prompt = ft_strdup(pwd);
	if (!(*prompt))
		*prompt = ft_strdup(BLUE "$ " RESET);
	else
	{
		temp = *prompt;
		*prompt = ft_strjoin(*prompt, BLUE "$ " RESET);
		free(temp);
	}
}

int	_readline(char **line, char **new_env, int *status, char *pwd)
{
	char	*prompt;

	init_prompt(&prompt, pwd);
	printf(GREEN);
	*line = readline(prompt);
	printf(RESET);
	free(prompt);
	if (!(*line))
	{
		free_ptr_arr(new_env);
		exit(EXIT_SUCCESS);
	}
	_add_history(*line);
	if (!(*line[0]) || count_pipes(*line) < 0
		|| check_quotes(*line) || valid_red(*line))
	{
		*status = (g_status == 130);
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}
