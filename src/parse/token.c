#include "minishell.h"

int isToken(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}