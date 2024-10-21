#include "minishell.h"

void	execute_echo(t_commands *current, t_mini *mini)
{
	int		i;
	bool	no_newline;

	i = 1;
	no_newline = false;
	while (current->cmds[i] && strcmp(current->cmds[i], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	while (current->cmds[i])
	{
		printf("%s", current->cmds[i]);
		if (current->cmds[i +1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	mini->exitcode = 0;
}

void	execute_exit(t_commands *current, t_mini *mini)
{
	int				exit_status;
	char			*endptr;

	(void)mini;
	exit_status = 0;
	printf("exit\n");
	if (current->cmds[1])
	{
		exit_status = strtol(current->cmds[1], &endptr, 10);
		if (*endptr != '\0')
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", current->cmds[1]);
			exit_status = 2;
		}
		else if (current->cmds[2])
		{
			fprintf(stderr, "exit: too many arguments\n");
			mini->exitcode = 1;
			return ;
		}
	}
	ft_gc_destroy_all_contexts();
	exit(exit_status);
}

void	execute_cd(t_commands *current, t_mini *mini)
{
	const char		*path;
	char			cwd[PATH_MAX];
	char			*old_pwd;

	if (current->cmds[1])
		path = current->cmds[1];
	else
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			mini->exitcode = 1;
			return ;
		}
	}
	if (strcmp(path, "-") == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			mini->exitcode = 1;
			return ;
		}
		printf ("%s\n", path);
	}
	old_pwd = getenv("PWD");
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
	if (chdir(path) != 0)
	{
		fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
		mini->exitcode = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		fprintf(stderr, "cd: error retrieving current directory: %s\n", strerror(errno));
	mini->exitcode = 0;
}

void	execute_pwd(t_commands *current, t_mini *mini)
{
	char			cwd[PATH_MAX];

	(void)current;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		mini->exitcode = 0;
	}
	else
	{
		fprintf(stderr, "pwd: error retrieving current directory: %s\n", strerror(errno));
		mini->exitcode = 1;
	}
}
