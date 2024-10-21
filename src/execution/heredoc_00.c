
#include "minishell.h"

void	handle_heredoc(t_commands *cmd)
{
	int				pipefd[2];
	char			*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, cmd->heredoc) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	cmd->fd_in = pipefd[0];
}

void	handle_builtin_redirections(t_commands *current)
{
	if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
	{
		current->saved_stdin = dup(STDIN_FILENO);
		if (dup2(current->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in");
			exit(EXIT_FAILURE);
		}
		close(current->fd_in);
	}
	if (current->fd_out != STDOUT_FILENO && current->fd_out > 0)
	{
		current->saved_stdout = dup(STDOUT_FILENO);
		if (dup2(current->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out");
			exit(EXIT_FAILURE);
		}
		close(current->fd_out);
	}
}

void	restore_builtin_redirections(t_commands *current)
{
	if (current->saved_stdin != -1)
	{
		dup2(current->saved_stdin, STDIN_FILENO);
		close(current->saved_stdin);
		current->saved_stdin = -1;
	}
	if (current->saved_stdout != -1)
	{
		dup2(current->saved_stdout, STDOUT_FILENO);
		close(current->saved_stdout);
		current->saved_stdout = -1;
	}
}
