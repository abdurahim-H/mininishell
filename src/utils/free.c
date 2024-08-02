#include "minishell.h"

void freeArr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		ft_gc_free(arr[i++]);
	ft_gc_free(arr);
}

char	**ft_realloc_char(char **ptr, int j)
{
	char	**new_ptr;
	int		i;

	i = 0;
	if (!ptr)
	{
		ptr = ft_calloc(1, sizeof(char *) * 2);
		return (ptr);
	}
	new_ptr = ft_gc_malloc(sizeof(char *) * (j + 2));
	if (!new_ptr)
		return (NULL);
	while (ptr[i])
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		i++;
	}
	while (i < j + 1)
		new_ptr[i++] = NULL;
	freeArr(ptr);
	return (new_ptr);
}