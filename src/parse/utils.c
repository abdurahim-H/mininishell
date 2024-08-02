#include "minishell.h"

void createPrompt(t_mini *mini, char *prompt)
{
	mini->prompt = ft_gc_malloc(sizeof(Prompt));
	mini->prompt->prom = ft_strdup(prompt);
	mini->prompt->i = 0;
	free(prompt);
	prompt = NULL;
}

void	skip_white_space(Prompt *prompt)
{
	while (prompt->prom[prompt->i] && iswhitespace(prompt->prom[prompt->i]))
	{
		(prompt->i)++;
	}
}

char *giveSubstr(char *str, int start, int end)
{
	char *newstr;

	newstr = ft_gc_malloc(end - start + 1);
	ft_memcpy(newstr, str + start, end - start);
	newstr[end - start] = '\0';
	return (newstr);
}

char	*ft_char_join(char *s1, char c)
{
	char	*result;
	size_t	len1;
	size_t	total_len;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	total_len = len1 + 1 + 1;
	result = (char *) ft_gc_malloc (total_len);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(result, s1);
	result[len1] = c;
	result[len1 + 1] = '\0';
	if (s1)
		ft_gc_free(s1);
	return (result);
}
