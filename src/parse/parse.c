#include "minishell.h"

void get_cmd(t_mini *mini, Token *token)
{
	char *prompt = NULL;
	char *quetos = NULL;

	if (isToken(mini->prompt->prom[mini->prompt->i]) || mini->prompt->prom[mini->prompt->i] == '\0')
		return ;
	while (mini->prompt->prom[mini->prompt->i] && !iswhitespace(mini->prompt->prom[mini->prompt->i]) && !isToken(mini->prompt->prom[mini->prompt->i]))
	{
		quetos = handle_quetos(mini->prompt);
		if (quetos)
			prompt = ft_strjoin_freeself(prompt, quetos);
		else
			prompt = ft_char_join(prompt, mini->prompt->prom[mini->prompt->i]);
		mini->prompt->i += 1;
	}
	token->type = COMMAND;
	token->text = prompt;
}

void get_pipe(t_mini *mini, Token *token)
{
	if (mini->prompt->prom[mini->prompt->i] == '|')
	{
		token->type = PIPE;
		token->text = findType(PIPE);
	}
	else
		return ;
}

void getEnd(t_mini *mini, Token *token)
{
	if (mini->prompt->prom[mini->prompt->i] == '\0')
	{
		token->type = END;
		token->text = findType(END);
	}
	else
		return ;
}

void parse_helper(t_mini *mini, Token *current)
{
	getEnd(mini, current);
	skip_white_space(mini->prompt);
	get_pipe(mini, current);
	get_cmd(mini, current);
	getInput(mini, current);
	getOutput(mini, current);
	mini->prompt->i += 1;
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
