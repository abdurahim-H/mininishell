#include "minishell.h"

void parse_init(t_mini *mini, char *prompt)
{
	createPrompt(mini, prompt);

	char **spliteed = ft_split(mini->prompt, ' ');

	int i = -1;

	while (spliteed[++i])
		printf("%s\n", spliteed[i]);

}