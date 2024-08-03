#include "minishell.h"

bool dolarToken(char c)
{
	return (isalnum(c) || c == '_');
}

char *handleDolar(t_mini *mini, Prompt *prompt)
{
	char *var;
	int start;

	if (prompt->prom[prompt->i] == '$')
	{
		prompt->i++;
		if (prompt->prom[prompt->i] == '?')
			return (ft_itoa(mini->exitcode));
		start = prompt->i;
		while (prompt->prom[prompt->i] && dolarToken(prompt->prom[prompt->i]))
		{
			prompt->i++;
		}
		var = giveSubstr(prompt->prom, start, prompt->i);
		prompt->i--;
		return (ft_strdup(getenv(var)));
	}
	return (NULL);
}

