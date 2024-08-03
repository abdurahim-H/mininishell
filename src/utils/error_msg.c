#include "minishell.h"


void syntaxError(t_mini *mini, char *c)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, c, ft_strlen(c));
	write(2, "'\n", 2);
	mini->exitcode = 258;
}