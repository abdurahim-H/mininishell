#include "minishell.h"

void quetoes_skipper(Prompt *pro)
{
	if (pro->prom[pro->i] == '\"')
	{
		(pro->i)++;
	}
	else
		return ;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\"')
	{
		pro->i++;
	}
}

char *giveQuetos(Prompt *pro)
{
	int start = pro->i;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\"')
	{
		pro->i++;
	}
	return (giveSubstr(pro->prom, start, pro->i));
}

char *handle_quetos(Prompt *prompt)
{
	char *newstr;

	if (prompt->prom[prompt->i] == '\"')
	{
		(prompt->i)++;
	}
	else
		return (NULL);
	newstr = giveQuetos(prompt);
	return (newstr);
}

