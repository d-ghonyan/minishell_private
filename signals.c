#include "minishell.h"

void	sigint_p(int signum);
void	sigint_c(int signum);

void	init_signals_parent(void)
{
	struct sigaction	action;

	action.sa_handler = SIG_IGN;
	signal(SIGINT, &sigint_p);
	sigaction(SIGQUIT, &action, NULL);
}

void	init_signals_child(void)
{
	struct sigaction	action;

	action.sa_handler = SIG_DFL;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	sigint_p(int signum)
{
	rl_done = 1;
}

void	sigint_c(int signum)
{
	if (signum == SIGQUIT)
		printf("Quit");
	printf("\n");
}
