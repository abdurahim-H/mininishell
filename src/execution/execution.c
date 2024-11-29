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

bool is_builtin(const char *cmd) {
	return (strcmp(cmd, "echo") == 0 ||
			strcmp(cmd, "cd") == 0 ||
			strcmp(cmd, "pwd") == 0 ||
			strcmp(cmd, "export") == 0 ||
			strcmp(cmd, "unset") == 0 ||
			strcmp(cmd, "env") == 0 ||
			strcmp(cmd, "exit") == 0);
}

void	check_pipelines(t_commands *current, bool *has_pipelines)
{
	while (current != NULL)
	{
		if (current->is_pipe)
			*has_pipelines = true;
		current = current->next;
	}
}

void	handle_pipes(int prev_pipe_fd[2], int pipe_fd[2], t_commands *current)
{
	if (prev_pipe_fd[0] != -1) {
		if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 prev_pipe_fd[0]");
		}
		close(prev_pipe_fd[0]);
		prev_pipe_fd[0] = -1;
	}
	if (current->is_pipe) {
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd[1]");
		}
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

void	execute_builtin_command(t_commands *current, t_mini *mini, int prev_pipe_fd[2], int pipe_fd[2])
{
	handle_pipes(prev_pipe_fd, pipe_fd, current);
	handle_builtin_redirections(current);
	execute_builtin(current, mini);
	restore_builtin_redirections(current);
	if (strcmp(current->cmds[0], "exit") == 0)
		exit(0);
}

void	setup_pipes(t_commands *current, int prev_pipe_fd[2], int pipe_fd[2])
{
	if (prev_pipe_fd[0] != -1)
	{
		if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 prev_pipe_fd[0]");
			exit(EXIT_FAILURE);
		}
	}
	if (current->is_pipe) {
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_fd[1]");
			exit(EXIT_FAILURE);
		}
	}
	if (prev_pipe_fd[0] != -1) close(prev_pipe_fd[0]);
	if (prev_pipe_fd[1] != -1) close(prev_pipe_fd[1]);
	if (current->is_pipe)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	handle_builtin_execution(t_commands *current, t_mini *mini)
{
	handle_builtin_redirections(current);
	execute_builtin(current, mini);
	restore_builtin_redirections(current);
	exit(mini->exitcode);
}

void	handle_heredoc_redirection(t_commands *current)
{
	handle_heredoc(current);
	if (current->fd_in == -1)
	{
		fprintf(stderr, "Error handling heredoc\n");
		exit(1);
	}
	if (dup2(current->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc fd_in");
		exit(1);
	}
	close(current->fd_in);
}

void	handle_input_redirection(t_commands *current)
{
	if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
	{
		if (dup2(current->fd_in, STDIN_FILENO) == -1) {
			perror("dup2 fd_in");
			exit(EXIT_FAILURE);
		}
		close(current->fd_in);
	}
}

void	handle_output_redirection(t_commands *current)
{
	if (current->fd_out != STDOUT_FILENO && current->fd_out > 0)
	{
		if (dup2(current->fd_out, STDOUT_FILENO) == -1) {
			perror("dup2 fd_out");
			exit(EXIT_FAILURE);
		}
		close(current->fd_out);
	}
}

void	execute_command(t_commands *current, t_mini *mini, char *cmd_path)
{
	if (execve(cmd_path, current->cmds, mini->envp) == -1)
	{
		fprintf(stderr, "%s: %s\n", current->cmds[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	execute_external_command(t_commands *current, t_mini *mini)
{
	char *cmd_path = find_command_path(current->cmds[0], mini);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", current->cmds[0]);
		exit(127);
	}
	if (current->heredoc)
	{
		handle_heredoc_redirection(current);
	}
	handle_input_redirection(current);
	handle_output_redirection(current);
	execute_command(current, mini, cmd_path);
}

void	execute_forked_command(t_commands *current, t_mini *mini, int prev_pipe_fd[2], int pipe_fd[2], bool current_is_builtin)
{
	setup_pipes(current, prev_pipe_fd, pipe_fd);
	if (current_is_builtin)
	{
		handle_builtin_execution(current, mini);
	} else {
		execute_external_command(current, mini);
	}
}

// void	setup_execution_environment(t_commands *current, t_mini *mini, int prev_pipe_fd[2], int pipe_fd[2], bool *execute_in_parent, bool *current_is_builtin, bool has_pipelines)
// {
// 	*current_is_builtin = is_builtin(current->cmds[0]);
// 	*execute_in_parent = *current_is_builtin && !has_pipelines;
// 	if (current->is_pipe)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			mini->exitcode = 1;
// 			return;
// 		}
// 	}
// 	(void)prev_pipe_fd[2];
// }

void setup_execution_environment(t_commands *current, t_mini *mini, int prev_pipe_fd[2], int pipe_fd[2], bool *execute_in_parent, bool *current_is_builtin, bool has_pipelines)
{
    if (!current || !current->cmds || !current->cmds[0]) {
        fprintf(stderr, "Error: Invalid command structure in setup_execution_environment\n");
        *execute_in_parent = false;
        *current_is_builtin = false;
        return;
    }

    *current_is_builtin = is_builtin(current->cmds[0]);
    *execute_in_parent = *current_is_builtin && !has_pipelines;

    if (current->is_pipe) {
        if (pipe(pipe_fd) == -1) {
        perror("pipe");
        mini->exitcode = 1;
        return;
        }
    }
    (void)prev_pipe_fd[2];
}


void	fork_and_execute(t_commands *current, t_mini *mini, int prev_pipe_fd[2],
						int pipe_fd[2], bool current_is_builtin)
{
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		mini->exitcode = 1;
		return;
	}
	if (pid == 0)
	{
		execute_forked_command(current, mini, prev_pipe_fd, pipe_fd, current_is_builtin);
	} else {
		if (prev_pipe_fd[1] != -1) close(prev_pipe_fd[1]);
		if (prev_pipe_fd[0] != -1) close(prev_pipe_fd[0]);
		prev_pipe_fd[0] = pipe_fd[0];
		prev_pipe_fd[1] = pipe_fd[1];
	}
}

void	execute_command_wrapper(t_commands *current, t_mini *mini, int prev_pipe_fd[2], bool has_pipelines)
{
	int pipe_fd[2] = {-1, -1};
	bool current_is_builtin;
	bool execute_in_parent;

	setup_execution_environment(current, mini, prev_pipe_fd, pipe_fd, &execute_in_parent, &current_is_builtin, has_pipelines);

	if (execute_in_parent)
	{
		execute_builtin_command(current, mini, prev_pipe_fd, pipe_fd);
	} else {
		fork_and_execute(current, mini, prev_pipe_fd, pipe_fd, current_is_builtin);
	}
}

void	initialize_execution(t_mini *mini, int *saved_stdin, int *saved_stdout, bool *has_pipelines)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	*has_pipelines = false;
	check_pipelines(mini->commands, has_pipelines);
}

void	finalize_execution(t_mini *mini, int saved_stdin, int saved_stdout)
{
	int status;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			mini->exitcode = WEXITSTATUS(status);
		else
			mini->exitcode = 1;
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

// void	execute_commands(t_mini *mini)
// {
// 	t_commands *current = mini->commands;
// 	int prev_pipe_fd[2] = {-1, -1};
// 	int saved_stdin, saved_stdout;
// 	bool has_pipelines;

// 	initialize_execution(mini, &saved_stdin, &saved_stdout, &has_pipelines);

// 	while (current != NULL)
// 	{
// 		execute_command_wrapper(current, mini, prev_pipe_fd, has_pipelines);
// 		current = current->next;
// 	}

// 	if (prev_pipe_fd[0] != -1) close(prev_pipe_fd[0]);
// 	if (prev_pipe_fd[1] != -1) close(prev_pipe_fd[1]);

// 	finalize_execution(mini, saved_stdin, saved_stdout);
// }


void execute_commands(t_mini *mini)
{
    t_commands *current = mini->commands;
    int prev_pipe_fd[2] = {-1, -1};
    int saved_stdin, saved_stdout;
    bool has_pipelines;

    initialize_execution(mini, &saved_stdin, &saved_stdout, &has_pipelines);

    while (current != NULL)
    {
        if (!current->cmds || !current->cmds[0]) {
            current = current->next;
            continue;
        }

        execute_command_wrapper(current, mini, prev_pipe_fd, has_pipelines);
        current = current->next;
    }

    if (prev_pipe_fd[0] != -1) close(prev_pipe_fd[0]);
    if (prev_pipe_fd[1] != -1) close(prev_pipe_fd[1]);

    finalize_execution(mini, saved_stdin, saved_stdout);
}
