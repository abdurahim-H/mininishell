#include "minishell.h"

void prompt_init(t_mini *mini, int exit_code)
{
	char *prompt;

	while (1)
	{
		prompt = readline("Minishell$ ");
		if (!prompt)
		{
			printf("exit\n");
			rl_clear_history();
			ft_gc_destroy_all_contexts();
			exit(EXIT_FAILURE);
		}
		add_history(prompt);
		mini->exitcode = exit_code;
		parse_init(mini, prompt);
		exit_code = mini->exitcode;
	}
	rl_clear_history();
	ft_gc_destroy_all_contexts();
}

void check_leaks(void)
{
	int ret = system("leaks minishell");
	if (ret == -1)
	{
		perror("system");
	}
}

int main(int ac, char **av, char **env)
{
	t_mini mini;
	int exit_code;

	atexit(check_leaks);
	exit_code = 0;
	prompt_init(&mini, exit_code);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}