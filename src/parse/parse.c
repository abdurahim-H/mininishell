#include "minishell.h"


void parse_helper(t_mini *mini, Token *current)
{
	
	skip_white_space(mini->prompt);
	if (getEnd(mini, current) == true)
		return ;
	if (get_pipe(mini, current) == true)
		return ;
	if (get_cmd(mini, current) == true)
		return ;
	if (getInput(mini, current) == true)
		return ;
	if (getOutput(mini, current) == true)
		return ;
}

void parse_init(t_mini *mini, char *prompt)
{
	Token *current;
	Token *newToken;

	current = NULL;
	mini->tokens = NULL;
	createPrompt(mini, prompt);
	while (true)
	{
		newToken = createToken();
		if (!newToken)
			return;
		if (!mini->tokens)
			mini->tokens = newToken;
		else
			current->next = newToken;
		current = newToken;
		parse_helper(mini, newToken);
		if (newToken->type == END)
			break ;
	}
	printTokens(mini->tokens);
	ft_gc_free(mini->prompt);
	mini->prompt = NULL;
}
