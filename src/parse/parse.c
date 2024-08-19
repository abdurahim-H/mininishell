#include "minishell.h"

void parse_helper(t_mini *mini, Token *current)
{
	skip_white_space(mini->prompt);
	if (getEnd(mini, current) == true)
		return;
	if (get_pipe(mini, current) == true)
		return;
	if (get_cmd(mini, current) == true)
		return;
	if (getInput(mini, current) == true)
		return;
	if (getOutput(mini, current) == true)
		return;
}

void start_token(t_mini *mini)
{
	Token *current;
	Token *newToken;

	current = NULL;
	mini->tokens = NULL;
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
			break;
	}
}

int initCommands(t_mini *mini)
{
	Token		*current;
	t_commands	*newCmd;

	current = mini->tokens;
	mini->commads = createCommands();
	newCmd = mini->commads;
	while (current != NULL)
	{
		if (!fillCommands(mini, newCmd, current))
			return (false);
		if (current->type == PIPE)
		{
			if (current->next->type == END)
				return (syntaxError(mini , "|"), false);
			newCmd->next = createCommands();
			if (!newCmd->next)
				return (false);
			newCmd = newCmd->next;
		}
		current = current->next;
	}
	return (true);
}

void parse_init(t_mini *mini, char *prompt)
{
	createPrompt(mini, prompt);
	start_token(mini);
	//printTokens(mini->tokens);
	if (initCommands(mini))
	{
		// exec from here;
	}
	printCmds(mini->commads);
	ft_gc_free(mini->prompt);
	clearTokens(mini);
	clear_cmds(mini->commads);
	mini->prompt = NULL;
}
