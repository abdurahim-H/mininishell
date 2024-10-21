#include "minishell.h"

char **duplicate_envp(char **envp)
{
    int     i;
    int     count;
    char    **new_envp;

    count = 0;
    while (envp[count])
        count++;
    new_envp = ft_gc_malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < count)
    {
        new_envp[i] = ft_strdup(envp[i]);
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

int main(int argc, char **argv, char **envp)
{
    t_mini  *mini;

    (void)argc;
    (void)argv;
    mini = ft_gc_malloc(sizeof(t_mini));
    mini->envp = duplicate_envp(envp);
    mini->exitcode = 0;
    while (1)
    {
        setup_signal_handlers();
        char *prompt = readline("minishell> ");
        if (!prompt)
        {
            printf("exit\n");
            ft_gc_destroy_all_contexts();
            exit(mini->exitcode);
        }
        if (*prompt)
            add_history(prompt);
        parse_init(mini, prompt);
    }
    return (0);
}
