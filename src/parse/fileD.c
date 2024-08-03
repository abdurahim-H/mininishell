#include "minishell.h"


int inOpener(char *name)
{
	int		fd;
	char	*msg;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		msg = ft_strjoin("bash: ", name);
		perror(msg);
		return (-1);
	}
	return (fd);
}

int outOpener(char *name)
{
	int		fd;
	char	*msg;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		msg = ft_strjoin("bash: ", name);
		perror(msg);
		return (-1);
	}
	return (fd);
}

int outApendOpener(char *name)
{
	int		fd;
	char	*msg;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		msg = ft_strjoin("bash: ", name);
		perror(msg);
		return (-1);
	}
	return (fd);
}
