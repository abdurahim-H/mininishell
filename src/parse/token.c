#include "minishell.h"

int get_cmd(t_mini *mini, Token *token)
{
	char *prompt;
	char *quetos;

	prompt = NULL;
	quetos = NULL;
	if (isToken(indexc(mini)) || indexc(mini) == '\0')
		return (false);
	while (indexc(mini) && !iswhitespace(indexc(mini)) && !isToken(indexc(mini)))
	{
		quetos = handle_quetos(mini, mini->prompt);
		if (quetos)
			prompt = ft_strjoin_freeself(prompt, quetos);
		else if (indexc(mini) == '$')
			prompt = ft_strjoin_freeself(prompt, handleDolar(mini, mini->prompt));
		else
			prompt = ft_char_join(prompt, indexc(mini));
		if (indexc(mini) && !iswhitespace(indexc(mini)) && !isToken(indexc(mini)))
			mini->prompt->i += 1;
	}
	token->type = COMMAND;
	token->text = prompt;
	return (true);
}

int get_pipe(t_mini *mini, Token *token)
{
	if (indexc(mini) == '|')
	{
		mini->prompt->i += 1;
		token->type = PIPE;
		token->text = findType(PIPE);
		return (true);
	}
	else
		return (false);
}

int getEnd(t_mini *mini, Token *token)
{
	if (indexc(mini) == '\0')
	{
		token->type = END;
		token->text = findType(END);
		return (true);
	}
	else
		return (false);
}

int getInput(t_mini *mini, Token *token)
{
	if (indexc(mini) == '<')
	{
		mini->prompt->i += 1;
		if (indexc(mini) == '<')
		{
			mini->prompt->i += 1;
			skip_white_space(mini->prompt);
			get_cmd(mini, token);
			token->text = get_heredoc(token->text);
			token->type = HEREDOC;
		}
		else
		{
			skip_white_space(mini->prompt);
			get_cmd(mini, token);
			token->type = REDIRECT_IN;
		}
		return (true);
	}
	else
		return (false);
}

int getOutput(t_mini *mini, Token *token)
{
	if (indexc(mini) == '>')
	{
		mini->prompt->i += 1;
		if (indexc(mini) == '>')
		{
			mini->prompt->i += 1;
			skip_white_space(mini->prompt);
			get_cmd(mini, token);
			token->type = REDIRECT_APPEND;
		}
		else
		{
			skip_white_space(mini->prompt);
			get_cmd(mini, token);
			token->type = REDIRECT_OUT;
		}
		return (true);
	}
	else
		return (false);
}
