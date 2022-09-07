/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/07 15:56:24 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

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
		*prompt = ft_strdup("\001" BLUE "\002" "minishell$ " "\001" RESET "\002");
	else
	{
		temp = *prompt;
		*prompt = ft_strjoin(*prompt, "\001" BLUE "\002" "$ " "\001" RESET "\002");
		free(temp);
	}
	temp = *prompt;
	*prompt = ft_strjoin("\001" GREEN "\002", *prompt);
	free(temp);
	temp = *prompt;
	*prompt = ft_strjoin(*prompt, "\001" RESET "\002");
	free(temp);
}

int	_readline(char **line, char **new_env, int *status, char *pwd)
{
	int		cond;
	char	*prompt;

	init_prompt(&prompt, pwd);
	*line = readline(prompt);
	free(prompt);
	if (!(*line))
	{
		free_ptr_arr(new_env);
		free(pwd);
		free(getoldpwd(NULL, 0));
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	_add_history(*line);
	cond = (count_pipes(*line) < 0 || check_quotes(*line) || valid_red(*line));
	if (!(*line[0]) || cond)
	{
		*status = (g_status == 130 || cond);
		g_status = 0;
		free(*line);
		return (1);
	}
	return (0);
}
