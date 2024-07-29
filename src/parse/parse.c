#include "minishell.h"





void parse_init(t_mini *mini, char *prompt)
{
	createPrompt(mini, prompt);
	printf("%s\n", mini->prompt);
}