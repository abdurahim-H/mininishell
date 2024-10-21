#include "minishell.h"

void	execute_env(t_commands *current, t_mini *mini)
{
	char	**env;

	env = mini->envp;
	if (current->cmds[1])
	{
		fprintf(stderr, "env: '%s': No such file or directory\n", current->cmds[1]);
		mini->exitcode = 127;
		return ;
	}
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	mini->exitcode = 0;
}

char	*ft_getenv(t_mini *mini, const char *name)
{
	size_t		name_len;
	int			i;

	i = 0;
	if (!name || strchr(name, '=') != NULL)
		return (NULL);
	name_len = strlen(name);
	while (mini->envp[i] != NULL)
	{
		if (strncmp(mini->envp[i], name, name_len) == 0 && mini->envp[i][name_len] == '=')
			return mini->envp[i] + name_len + 1;
		i++;
	}

    return (NULL);
}

int	find_env_index(char **envp, const char *name)
{
	size_t		name_len;
	int			i;

	name_len = strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int ft_setenv(t_mini *mini, const char *name, const char *value)
{
    int index = find_env_index(mini->envp, name);
    char *new_entry;
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);

    new_entry = malloc(name_len + value_len + 2);
    if (!new_entry)
    {
        perror("ft_setenv: malloc failed");
        return (-1);
    }
    sprintf(new_entry, "%s=%s", name, value);

    if (index != -1)
    {
        free(mini->envp[index]);
        mini->envp[index] = new_entry;
    }
    else
    {
        // Count existing environment variables
        int count = 0;
        while (mini->envp[count])
            count++;

        // Reallocate envp to hold the new variable and NULL terminator
        char **new_envp = realloc(mini->envp, sizeof(char *) * (count + 2));
        if (!new_envp)
        {
            free(new_entry);
            perror("ft_setenv: realloc failed");
            return (-1);
        }

        // Add the new environment variable
        new_envp[count] = new_entry;
        new_envp[count + 1] = NULL;

        // Update mini->envp to point to the new array
        mini->envp = new_envp;
    }

    return (0);
}



void execute_export(t_commands *current, t_mini *mini)
{
	int i;
	char *arg;
	char *equal_sign;
	char *key;
	char *value;
	int all_valid = 1;

	i = 1;
	mini->exitcode = 0;
	if (current->cmds[1] == NULL)
	{
		char **env = mini->envp;
		while (*env)
		{
			printf("declare -x %s\n", *env);
			env++;
		}
		return;
	}
	while (current->cmds[i])
	{
		arg = current->cmds[i];
		equal_sign = strchr(arg, '=');
		if (equal_sign)
		{
			size_t key_len = equal_sign - arg;
			key = strndup(arg, key_len);
			if (!key)
			{
				fprintf(stderr, "export: memory allocation error\n");
				mini->exitcode = 1;
				all_valid = 0;
				break;
			}
			if (!is_valid_identifier(key))
			{
				fprintf(stderr, "export: '%s': not a valid identifier\n", arg);
				free(key);
				mini->exitcode = 1;
				all_valid = 0;
				break;
			}
			free(key);
		}
		else
		{
			if (!is_valid_identifier(arg))
			{
				fprintf(stderr, "export: '%s': not a valid identifier\n", arg);
				mini->exitcode = 1;
				all_valid = 0;
				break;
			}
		}
		i++;
	}
	if (all_valid)
	{
		i = 1;
		while (current->cmds[i])
		{
			arg = current->cmds[i];
			equal_sign = strchr(arg, '=');
			if (equal_sign)
			{
				size_t key_len = equal_sign - arg;
				key = strndup(arg, key_len);
				value = equal_sign + 1;
			}
			else
			{
				key = strdup(arg);
				value = ft_getenv(mini, key);
				if (!value)
					value = "";
			}
			if (ft_setenv(mini, key, value) != 0)
			{
				fprintf(stderr, "export: error setting variable '%s'\n", key);
				mini->exitcode = 1;
			}
			free(key);
			i++;
		}
	}
}

int	is_valid_identifier(const char *key)
{
	int			i;

	i = 0;
	if (!key || (!isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!isalnum(key[i]) && key[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	remove_env_var(t_mini *mini, const char *var_name)
{
	int index = find_env_index(mini->envp, var_name);
	if (index == -1)
	{
		fprintf(stderr, "unset: '%s': not found\n", var_name);
		mini->exitcode = 1;
		return;
	}

	free(mini->envp[index]);
	for (int i = index; mini->envp[i] != NULL; i++)
	{
		mini->envp[i] = mini->envp[i + 1];
	}
}

void	execute_unset(t_commands *current, t_mini *mini)
{
	int				i;
	char			*var_name;
	
	mini->exitcode = 0;
	i = 1;
	if (current->cmds[1] == NULL)
	{
		fprintf(stderr, "unset: not enough arguments\n");
		return ;
	}
	while (current->cmds[i])
	{
		var_name = current->cmds[i];
		if(!is_valid_identifier(var_name))
		{
			fprintf(stderr, "unset: '%s': not a valid identifier\n", var_name);
			mini->exitcode = 1;
			i++;
			continue;
		}
		remove_env_var(mini, var_name);
		i++;
	}
}