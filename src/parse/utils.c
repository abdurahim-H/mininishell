#include "minishell.h"

char	*ft_strdup_gb(const char *s1)
{
	char	*s2;
	int		len;

	if (!s1)
		return ("");
	len = ft_strlen(s1);
	s2 = (char *) ft_gc_malloc ((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}

void createPrompt(t_mini *mini, char *prompt)
{
	mini->prompt = ft_strdup_gb(prompt);
	free(prompt);
	prompt = NULL;
}