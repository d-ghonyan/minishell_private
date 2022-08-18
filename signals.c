/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/03/10 20:46:54 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_p(int signum);

void	init_signals_parent(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	sigemptyset(&(action.sa_mask));
	action.sa_handler = SIG_IGN;
	signal(SIGINT, &sigint_p);
	sigaction(SIGQUIT, &action, NULL);
}

void	init_signals_child(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	sigemptyset(&(action.sa_mask));
	action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	init_signals_heredoc(void)
{
	struct sigaction	action;

	action.sa_flags = 0;
	sigemptyset(&(action.sa_mask));
	action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &action, NULL);
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}
