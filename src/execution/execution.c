#include "minishell.h"

void	execute_builtin(t_commands *current, t_mini *mini)
{
	if (strcmp(current->cmds[0], "echo") == 0)
		execute_echo(current, mini);
	else if (strcmp(current->cmds[0], "exit") == 0)
		execute_exit(current, mini);
	else if (strcmp(current->cmds[0], "cd") == 0)
		execute_cd(current, mini);
	else if (strcmp(current->cmds[0], "pwd") == 0)
		execute_pwd(current, mini);
	else if (strcmp(current->cmds[0], "env") == 0)
		execute_env(current, mini);
	else if (strcmp(current->cmds[0], "export") == 0)
		execute_export(current, mini);
	else if (strcmp(current->cmds[0], "unset") == 0)
		execute_unset(current, mini);
}

void	execute_commands(t_mini *mini)
{
	t_commands		*current;
	pid_t			pid;
	int				status;
	char			*cmd_path;

	current = mini->commands;
	while (current != NULL)
	{
		if (current->cmds == NULL || current->cmds[0] == NULL)
		{
			current = current->next;
			continue;
		}
		if (current->heredoc)
		{
			handle_heredoc(current);
		}
		if (strcmp(current->cmds[0], "echo") == 0 ||
			strcmp(current->cmds[0], "cd") == 0 ||
			strcmp(current->cmds[0], "pwd") == 0 ||
			strcmp(current->cmds[0], "export") == 0 ||
			strcmp(current->cmds[0], "unset") == 0 ||
			strcmp(current->cmds[0], "env") == 0 ||
			strcmp(current->cmds[0], "exit") == 0)
		{
			handle_builtin_redirections(current);
			execute_builtin(current, mini);
			restore_builtin_redirections(current);
		}
		else
		{
			cmd_path = find_command_path(current->cmds[0], mini);
			if (!cmd_path)
			{
				fprintf(stderr, "%s: command not found\n", current->cmds[0]);
				mini->exitcode = 127;
				current = current->next;
				continue;
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				mini->exitcode = 1;
				ft_gc_free(cmd_path);
				return;
			}
			if (pid == 0)
			{
				if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
				{
					if (dup2(current->fd_in, STDIN_FILENO) == -1)
					{
						perror("dup2 fd_in");
						exit(EXIT_FAILURE);
					}
					close(current->fd_in);
				}
				if (current->fd_out != STDOUT_FILENO && current->fd_out > 0)
				{
					if (dup2(current->fd_out, STDOUT_FILENO) == -1)
					{
						perror("dup2 fd_out");
						exit(EXIT_FAILURE);
					}
					close(current->fd_out);
				}
				if (execve(cmd_path, current->cmds, mini->envp) == -1)
				{
					fprintf(stderr, "%s: %s\n", current->cmds[0], strerror(errno));
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					mini->exitcode = WEXITSTATUS(status);
				else
					mini->exitcode = 1;
			}
			ft_gc_free(cmd_path);
		}
		current = current->next;
	}
}
