#include "minishell.h"

Token *createToken()
{
	Token *newToken;

	newToken = (Token *)ft_gc_malloc(sizeof(Token));
	if (!newToken)
		return NULL;
	newToken->type = 0;
	newToken->text = NULL;
	newToken->next = NULL;
	return (newToken);
}

char *findType(int type)
{
	if (type == COMMAND)
		return ("COMMAND");
	else if (type == PIPE)
		return ("|");
	else if (type == REDIRECT_IN)
		return ("<");
	else if (type == REDIRECT_OUT)
		return (">");
	else if (type == REDIRECT_APPEND)
		return (">>");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == END)
		return ("newline");
	else
		return ("INVALID");
}

void clearTokens(t_mini *mini)
{
	Token *tmp;
	while (mini->tokens)
	{
		tmp = mini->tokens;
		mini->tokens = mini->tokens->next;
		ft_gc_free(tmp->text);
		ft_gc_free(tmp);
	}
	mini->tokens = NULL;
}