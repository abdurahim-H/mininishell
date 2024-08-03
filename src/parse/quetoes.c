#include "minishell.h"

static char *giveQuetos(t_mini *mini, Prompt *pro)
{
	int		start;
	char	*str;
	
	str = NULL;
	start = pro->i;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\"')
	{
		if (pro->prom[pro->i] == '$')
			str = ft_strjoin_freeself(str, handleDolar(mini, pro));
		else
			str = ft_char_join(str, pro->prom[pro->i]);
		pro->i++;
	}
	return (str);
}

static char *giveSingleQuetos(Prompt *pro)
{
	int start;

	start = pro->i;
	while (pro->prom[pro->i] && pro->prom[pro->i] != '\'')
	{
		pro->i++;
	}
	printf("%d\n", pro->prom[pro->i]);
	return (giveSubstr(pro->prom, start, pro->i));
}

char *handle_quetos(t_mini *mini, Prompt *prompt)
{
	char *newstr;

	if (prompt->prom[prompt->i] == '\"')
	{
		(prompt->i)++;
		newstr = giveQuetos(mini, prompt);
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
	ft_gc_free(stop);
	return (str);
}
