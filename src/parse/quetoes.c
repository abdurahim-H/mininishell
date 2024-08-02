#include "minishell.h"

static char *giveQuetos(Prompt *pro)
{
	int start = pro->i;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\"')
	{
		pro->i++;
	}
	return (giveSubstr(pro->prom, start, pro->i));
}

static char *giveSingleQuetos(Prompt *pro)
{
	int start;

	start = pro->i;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\'')
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
		newstr = giveQuetos(prompt);
	}
	else if (prompt->prom[prompt->i] == '\'')
	{
		(prompt->i)++;
		newstr = giveSingleQuetos(prompt);
	}
	else
		return (NULL);
	return (newstr);
}

char *get_heredoc(char *stop)
{
	char *str;
	char *line;

	str = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, stop) == 0)
		{
			free(line);
			break;
		}
		str = ft_strjoin_freeself(str, line);
		str = ft_strjoin_freeself(str, "\n");
		free(line);
	}
	return (str);
}