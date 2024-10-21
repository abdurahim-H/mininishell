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

char	**duplicate_envp(char **envp)
{
    int count = 0;
    while (envp[count])
        count++;
    char **new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++)
    {
        new_envp[i] = strdup(envp[i]);
        if (!new_envp[i])
        {
            perror("strdup");
            // Handle cleanup if necessary
        }
    }
    new_envp[count] = NULL;
    return new_envp;
}


int main(int argc, char **argv, char **envp)
{
	t_mini  *mini;

	(void)argc;
	(void)argv;
	mini = ft_gc_malloc(sizeof(t_mini));
	mini->envp = duplicate_envp(envp);
	mini->exitcode = 0;

	setup_signal_handlers();
	prompt_init(mini, mini->exitcode);

	return (0);
}
