#include "minishell.h"

void	my_free_split(char **strs)
{
	int i;

	if (!strs)
		return;

	i = 0;
	while (strs[i])
	{
		ft_gc_free(strs[i]);
		i++;
	}
	ft_gc_free(strs);
}

char	*my_ft_strjoin(const char *s1, const char *s2)
{
	char			*joined;
	size_t			len1;
	size_t			len2;

	if (!s1 || !s2)
		return (NULL);

	len1 = strlen(s1);
	len2 = strlen(s2);

	joined = ft_gc_malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);

	strcpy(joined, s1);
	strcat(joined, s2);

	return (joined);
}

char	*my_ft_strdup(const char *s1)
{
	char			*dup;
	size_t			len;

	if (!s1)
		return (NULL);

	len = strlen(s1);
	dup = ft_gc_malloc(len + 1);
	if (!dup)
		return (NULL);

	strcpy(dup, s1);
	return (dup);
}

char	*my_ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			s_len;

	if (!s)
		return (NULL);

	s_len = strlen(s);
	if (start >= s_len)
		return (my_ft_strdup(""));

	if (len > s_len - start)
		len = s_len - start;

	substr = ft_gc_malloc(len + 1);
	if (!substr)
		return (NULL);

	strncpy(substr, s + start, len);
	substr[len] = '\0';

	return (substr);
}

char	**my_ft_split(const char *s, char c)
{
	char			**result;
	size_t			count;
	size_t			i;
	size_t			j;
	size_t			start;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	result = ft_gc_malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			result[j] = my_ft_substr(s, start, i - start);
			if (!result[j++])
			{
				my_free_split(result);
				return (NULL);
			}
		}
	}
	result[j] = NULL;
	return (result);
}

char	*my_ft_getenv(t_mini *mini, const char *name)
{
	size_t			name_len;
	int				i;

	if (!name || strchr(name, '=') != NULL)
		return (NULL);

	name_len = strlen(name);
	i = 0;
	while (mini->envp[i] != NULL)
	{
		if (strncmp(mini->envp[i], name, name_len) == 0 && mini->envp[i][name_len] == '=')
			return (mini->envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

char	*my_ft_strjoin_freeself(char *s1, const char *s2)
{
	char			*joined;
	size_t			len1;
	size_t			len2;

	if (!s1 || !s2)
	{
		ft_gc_free(s1);
		return (NULL);
	}
	len1 = strlen(s1);
	len2 = strlen(s2);

	joined = ft_gc_malloc(len1 + len2 + 1);
	if (!joined)
	{
		ft_gc_free(s1);
		return (NULL);
	}

	strcpy(joined, s1);
	strcat(joined, s2);

	ft_gc_free(s1);
	return (joined);
}

char	*find_command_path(const char *cmd, t_mini *mini)
{
	char			*path_env;
	char			**dirs;
	char			*full_path;
	int				i;
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (my_ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = my_ft_getenv(mini, "PATH");
	if (!path_env)
		return (NULL);
	dirs = my_ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = my_ft_strjoin(dirs[i], "/");
		if (!full_path)
		{
			my_free_split(dirs);
			return (NULL);
		}
		full_path = my_ft_strjoin_freeself(full_path, cmd);
		if (!full_path)
		{
			my_free_split(dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			my_free_split(dirs);
			return (full_path);
		}
		ft_gc_free(full_path);
		i++;
	}
	my_free_split(dirs);
	return (NULL);
}