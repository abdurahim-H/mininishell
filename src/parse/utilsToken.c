#include "minishell.h"

Token *createToken()
{
	Token *newToken;
	
	newToken = (Token *) ft_gc_malloc (sizeof(Token));
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
	else if (type == ARGUMENT)
		return ("ARGUMENT");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == BACKGROUND)
		return ("BACKGROUND");
	else if (type == SEMICOLON)
		return ("SEMICOLON");
	else if (type == END)
		return ("END");
	else
		return ("INVALID");
}

void printTokens(Token *head)
{
	Token *current = head;
	int i;

	i = 0;
	while (current != NULL)
	{
		printf("Token : %d\n", ++i);
		printf("Type  : %s\n", findType(current->type));
		printf("Text  : %s\n", current->text);
		printf("------------------------------------------------\n");
		current = current->next;
	}
}