#include "minishell.h"

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\nminishell> ", 11);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}


void	sigquit_handler(int sig)
{
	(void)sig;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, SIG_IGN);
}
