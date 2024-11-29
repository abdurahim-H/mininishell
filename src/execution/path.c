#include "minishell.h"

// void	my_free_split(char **strs)
// {
// 	int i;

// 	if (!strs)
// 		return;

// 	i = 0;
// 	while (strs[i])
// 	{
// 		ft_gc_free(strs[i]);
// 		i++;
// 	}
// 	ft_gc_free(strs);
// }

// char	*my_ft_strjoin(const char *s1, const char *s2)
// {
// 	char			*joined;
// 	size_t			len1;
// 	size_t			len2;

// 	if (!s1 || !s2)
// 		return (NULL);

// 	len1 = strlen(s1);
// 	len2 = strlen(s2);

// 	joined = ft_gc_malloc(len1 + len2 + 1);
// 	if (!joined)
// 		return (NULL);

// 	strcpy(joined, s1);
// 	strcat(joined, s2);

// 	return (joined);
// }

// char	*my_ft_strdup(const char *s1)
// {
// 	char			*dup;
// 	size_t			len;

// 	if (!s1)
// 		return (NULL);

// 	len = strlen(s1);
// 	dup = ft_gc_malloc(len + 1);
// 	if (!dup)
// 		return (NULL);

// 	strcpy(dup, s1);
// 	return (dup);
// }

// char	*my_ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	char			*substr;
// 	size_t			s_len;

// 	if (!s)
// 		return (NULL);

// 	s_len = strlen(s);
// 	if (start >= s_len)
// 		return (my_ft_strdup(""));

// 	if (len > s_len - start)
// 		len = s_len - start;

// 	substr = ft_gc_malloc(len + 1);
// 	if (!substr)
// 		return (NULL);

// 	strncpy(substr, s + start, len);
// 	substr[len] = '\0';

// 	return (substr);
// }

// char	**my_ft_split(const char *s, char c)
// {
// 	char			**result;
// 	size_t			count;
// 	size_t			i;
// 	size_t			j;
// 	size_t			start;

// 	if (!s)
// 		return (NULL);
// 	count = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 	}
// 	result = ft_gc_malloc(sizeof(char *) * (count + 1));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		start = i;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (i > start)
// 		{
// 			result[j] = my_ft_substr(s, start, i - start);
// 			if (!result[j++])
// 			{
// 				my_free_split(result);
// 				return (NULL);
// 			}
// 		}
// 	}
// 	result[j] = NULL;
// 	return (result);
// }

// char	*my_ft_getenv(t_mini *mini, const char *name)
// {
// 	size_t			name_len;
// 	int				i;

// 	if (!name || strchr(name, '=') != NULL)
// 		return (NULL);

// 	name_len = strlen(name);
// 	i = 0;
// 	while (mini->envp[i] != NULL)
// 	{
// 		if (strncmp(mini->envp[i], name, name_len) == 0 && mini->envp[i][name_len] == '=')
// 			return (mini->envp[i] + name_len + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*my_ft_strjoin_freeself(char *s1, const char *s2)
// {
// 	char			*joined;
// 	size_t			len1;
// 	size_t			len2;

// 	if (!s1 || !s2)
// 	{
// 		ft_gc_free(s1);
// 		return (NULL);
// 	}
// 	len1 = strlen(s1);
// 	len2 = strlen(s2);

// 	joined = ft_gc_malloc(len1 + len2 + 1);
// 	if (!joined)
// 	{
// 		ft_gc_free(s1);
// 		return (NULL);
// 	}

// 	strcpy(joined, s1);
// 	strcat(joined, s2);

// 	ft_gc_free(s1);
// 	return (joined);
// }

// char	*find_command_path(const char *cmd, t_mini *mini)
// {
// 	char			*path_env;
// 	char			**dirs;
// 	char			*full_path;
// 	int				i;
// 	if (strchr(cmd, '/'))
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			return (my_ft_strdup(cmd));
// 		else
// 			return (NULL);
// 	}
// 	path_env = my_ft_getenv(mini, "PATH");
// 	if (!path_env)
// 	{
// 		fprintf(stderr, "Warning: PATH is not set.\n");
// 		return (NULL);
// 	}
// 	dirs = my_ft_split(path_env, ':');
// 	if (!dirs)
// 		return (NULL);
// 	i = 0;
// 	while (dirs[i])
// 	{
// 		if (dirs[i][0] == '\0')
// 		{
// 			i++;
// 			continue;
// 		}
// 		full_path = my_ft_strjoin(dirs[i], "/");
// 		if (!full_path)
// 		{
// 			my_free_split(dirs);
// 			return (NULL);
// 		}
// 		full_path = my_ft_strjoin_freeself(full_path, cmd);
// 		if (!full_path)
// 		{
// 			my_free_split(dirs);
// 			return (NULL);
// 		}
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			my_free_split(dirs);
// 			return (full_path);
// 		}
// 		ft_gc_free(full_path);
// 		i++;
// 	}
// 	my_free_split(dirs);
// 	return (NULL);
// }

//------------------------------------------------------------------------//

void my_free_split(char **strs)
{
    int i;

    if (!strs)
        return;

    i = 0;
    while (strs[i]) {
        ft_gc_free(strs[i]);
        i++;
    }
    ft_gc_free(strs);
}

char *my_ft_strdup(const char *s1)
{
    char *dup;
    size_t len;

    if (!s1)
        return NULL;

    len = strlen(s1);
    dup = ft_gc_malloc(len + 1);
    if (!dup)
        return NULL;

    strcpy(dup, s1);
    return dup;
}

char *my_ft_substr(const char *s, unsigned int start, size_t len)
{
    char *substr;
    size_t s_len;

    if (!s)
        return NULL;

    s_len = strlen(s);
    if (start >= s_len)
        return my_ft_strdup("");

    if (len > s_len - start)
        len = s_len - start;

    substr = ft_gc_malloc(len + 1);
    if (!substr)
        return NULL;

    strncpy(substr, s + start, len);
    substr[len] = '\0';

    return substr;
}

char *my_ft_strjoin(const char *s1, const char *s2)
{
    char *joined;
    size_t len1;
    size_t len2;

    if (!s1 || !s2)
        return NULL;

    len1 = strlen(s1);
    len2 = strlen(s2);

    joined = ft_gc_malloc(len1 + len2 + 1);
    if (!joined)
        return NULL;

    strcpy(joined, s1);
    strcat(joined, s2);

    return joined;
}

char *my_ft_strjoin_freeself(char *s1, const char *s2)
{
    char *joined;
    size_t len1;
    size_t len2;

    if (!s1 || !s2) {
        ft_gc_free(s1);
        return NULL;
    }
    len1 = strlen(s1);
    len2 = strlen(s2);

    joined = ft_gc_malloc(len1 + len2 + 1);
    if (!joined) {
        ft_gc_free(s1);
        return NULL;
    }

    strcpy(joined, s1);
    strcat(joined, s2);

    ft_gc_free(s1);
    return joined;
}

char *my_ft_getenv(t_mini *mini, const char *name)
{
    size_t name_len;
    int i;

    if (!name || strchr(name, '=') != NULL)
        return NULL;

    name_len = strlen(name);
    i = 0;
    while (mini->envp[i] != NULL) {
        if (strncmp(mini->envp[i], name, name_len) == 0 && mini->envp[i][name_len] == '=')
            return mini->envp[i] + name_len + 1;
        i++;
    }
    return NULL;
}

char **my_ft_split(const char *s, char c)
{
    char **result;
    size_t count;

    if (!s)
        return NULL;
    count = count_words(s, c);
    result = allocate_split_result(count);
    if (!result)
        return NULL;
    if (!populate_split_result(result, s, c))
        return NULL;
    return result;
}

/**
 * Counts the number of words separated by the delimiter.
 *
 * @param s The input string.
 * @param delimiter The delimiter character.
 * @return Number of words.
 */
size_t count_words(const char *s, char delimiter)
{
    size_t count = 0;
    size_t i = 0;

    while (s[i]) {
        while (s[i] == delimiter)
            i++;
        if (s[i])
            count++;
        while (s[i] && s[i] != delimiter)
            i++;
    }
    return count;
}

/**
 * Allocates memory for the split result array.
 *
 * @param count Number of words.
 * @return Allocated array or NULL on failure.
 */
char **allocate_split_result(size_t count)
{
    char **result;

    result = ft_gc_malloc(sizeof(char *) * (count + 1));
    if (!result)
        return NULL;
    return result;
}

/**
 * Populates the split result array with substrings.
 *
 * @param result The array to populate.
 * @param s The input string.
 * @param delimiter The delimiter character.
 * @return true on success, false on failure.
 */
bool populate_split_result(char **result, const char *s, char delimiter)
{
    size_t i = 0;
    size_t j = 0;
    size_t start;

    while (s[i]) {
        while (s[i] == delimiter)
            i++;
        start = i;
        while (s[i] && s[i] != delimiter)
            i++;
        if (i > start) {
            result[j] = my_ft_substr(s, start, i - start);
            if (!result[j++]) {
                my_free_split(result);
                return false;
            }
        }
    }
    result[j] = NULL;
    return true;
}

/**
 * Finds the full path of a command by searching in PATH or using direct paths.
 *
 * @param cmd The command to find.
 * @param mini Pointer to the minishell structure containing environment variables.
 * @return Full path to the executable or NULL if not found.
 */
char *find_command_path(const char *cmd, t_mini *mini)
{
    if (strchr(cmd, '/'))
        return get_path_direct_command(cmd);
    return search_in_paths(mini, cmd);
}

/**
 * Handles commands that contain '/' by checking their executability.
 *
 * @param cmd The command with a direct path.
 * @return Duplicated command path if executable, else NULL.
 */
char *get_path_direct_command(const char *cmd)
{
    if (access(cmd, X_OK) == 0)
        return my_ft_strdup(cmd);
    return NULL;
}

/**
 * Constructs the full path by concatenating directory and command.
 *
 * @param dir The directory path.
 * @param cmd The command name.
 * @return The full path to the command or NULL on failure.
 */
char *construct_full_path(const char *dir, const char *cmd)
{
    char *path;
    char *temp;

    path = my_ft_strjoin(dir, "/");
    if (!path)
        return NULL;
    temp = my_ft_strjoin_freeself(path, cmd);
    return temp;
}

/**
 * Retrieves and splits the PATH environment variable.
 *
 * @param mini Pointer to the minishell structure containing environment variables.
 * @return Array of directory strings or NULL on failure.
 */
char **get_split_path(t_mini *mini)
{
    char *path_env = my_ft_getenv(mini, "PATH");
    if (!path_env) {
        fprintf(stderr, "Warning: PATH is not set.\n");
        return NULL;
    }
    return my_ft_split(path_env, ':');
}

/**
 * Iterates through directories to find the executable command.
 *
 * @param dirs Array of directory strings.
 * @param cmd The command to find.
 * @return Full path to the executable or NULL if not found.
 */
char *find_executable_in_dirs(char **dirs, const char *cmd)
{
    int i;
    char *full_path;

    i = 0;
    while (dirs[i]) {
        if (dirs[i][0] != '\0') {
            full_path = construct_full_path(dirs[i], cmd);
            if (!full_path)
                return NULL;
            if (access(full_path, X_OK) == 0)
                return full_path;
            ft_gc_free(full_path);
        }
        i++;
    }
    return NULL;
}

/**
 * Searches for the command in the PATH directories.
 *
 * @param mini Pointer to the minishell structure containing environment variables.
 * @param cmd The command to find.
 * @return Full path to the executable or NULL if not found.
 */
char *search_in_paths(t_mini *mini, const char *cmd)
{
    char **dirs;
    char *full_path;

    dirs = get_split_path(mini);
    if (!dirs)
        return NULL;

    full_path = find_executable_in_dirs(dirs, cmd);
    my_free_split(dirs);
    return full_path;
}
