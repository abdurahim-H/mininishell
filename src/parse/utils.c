#include "minishell.h"

void createPrompt(t_mini *mini, char *prompt)
{
	mini->prompt = ft_strdup(prompt);
	free(prompt);
	prompt = NULL;
}
