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

// void execute_commands(t_mini *mini)
// {
//     t_commands *current = mini->commands;
//     int prev_pipe_fd[2] = {-1, -1};
//     pid_t pid;
//     int status;
//     int saved_stdin = dup(STDIN_FILENO);
//     int saved_stdout = dup(STDOUT_FILENO);

//     while (current != NULL)
//     {
//         int pipe_fd[2] = {-1, -1};

//         // If the current command is followed by a pipe, create a new pipe
//         if (current->is_pipe)
//         {
//             if (pipe(pipe_fd) == -1)
//             {
//                 perror("pipe");
//                 mini->exitcode = 1;
//                 return;
//             }
//         }

//         // Fork a child process for the current command
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             mini->exitcode = 1;
//             return;
//         }

//         if (pid == 0)
//         {
//             // In child process

//             // If there's a previous pipe, set it as stdin
//             if (prev_pipe_fd[0] != -1)
//             {
//                 if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
//                 {
//                     perror("dup2 prev_pipe_fd[0]");
//                     exit(EXIT_FAILURE);
//                 }
//             }

//             // If there's a current pipe, set its write end as stdout
//             if (current->is_pipe)
//             {
//                 if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
//                 {
//                     perror("dup2 pipe_fd[1]");
//                     exit(EXIT_FAILURE);
//                 }
//             }

//             // Close unused file descriptors in the child
//             if (prev_pipe_fd[0] != -1)
//             {
//                 close(prev_pipe_fd[0]);
//             }
//             if (prev_pipe_fd[1] != -1)
//             {
//                 close(prev_pipe_fd[1]);
//             }
//             if (current->is_pipe)
//             {
//                 close(pipe_fd[0]);
//                 close(pipe_fd[1]);
//             }

//             // Handle built-in commands
//             if (strcmp(current->cmds[0], "echo") == 0 ||
//                 strcmp(current->cmds[0], "cd") == 0 ||
//                 strcmp(current->cmds[0], "pwd") == 0 ||
//                 strcmp(current->cmds[0], "export") == 0 ||
//                 strcmp(current->cmds[0], "unset") == 0 ||
//                 strcmp(current->cmds[0], "env") == 0 ||
//                 strcmp(current->cmds[0], "exit") == 0)
//             {
//                 handle_builtin_redirections(current);
//                 execute_builtin(current, mini);
//                 restore_builtin_redirections(current);
//                 exit(mini->exitcode);
//             }
//             else
//             {
//                 // Execute external command
//                 char *cmd_path = find_command_path(current->cmds[0], mini);
//                 if (!cmd_path)
//                 {
//                     fprintf(stderr, "%s: command not found\n", current->cmds[0]);
//                     exit(127);
//                 }

//                 // Handle heredoc if present
//                 if (current->heredoc)
//                 {
//                     handle_heredoc(current);
//                     if (current->fd_in == -1)
//                     {
//                         fprintf(stderr, "Error handling heredoc\n");
//                         exit(1);
//                     }
//                     if (dup2(current->fd_in, STDIN_FILENO) == -1)
//                     {
//                         perror("dup2 heredoc fd_in");
//                         exit(1);
//                     }
//                     close(current->fd_in);
//                 }

//                 // Handle input redirection
//                 if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
//                 {
//                     if (dup2(current->fd_in, STDIN_FILENO) == -1)
//                     {
//                         perror("dup2 fd_in");
//                         exit(EXIT_FAILURE);
//                     }
//                     close(current->fd_in);
//                 }

//                 // Handle output redirection
//                 if (current->fd_out != STDOUT_FILENO && current->fd_out > 0)
//                 {
//                     if (dup2(current->fd_out, STDOUT_FILENO) == -1)
//                     {
//                         perror("dup2 fd_out");
//                         exit(EXIT_FAILURE);
//                     }
//                     close(current->fd_out);
//                 }

//                 if (execve(cmd_path, current->cmds, mini->envp) == -1)
//                 {
//                     fprintf(stderr, "%s: %s\n", current->cmds[0], strerror(errno));
//                     exit(EXIT_FAILURE);
//                 }
//             }
//         }
//         else
//         {
//             // In parent process

//             // Close the write end of the previous pipe as it's no longer needed
//             if (prev_pipe_fd[1] != -1)
//                 close(prev_pipe_fd[1]);

//             // Close the read end of the previous pipe as it's no longer needed
//             if (prev_pipe_fd[0] != -1)
//                 close(prev_pipe_fd[0]);

//             // Update prev_pipe_fd to the current pipe_fd for the next iteration
//             prev_pipe_fd[0] = pipe_fd[0];
//             prev_pipe_fd[1] = pipe_fd[1];
//         }

//         current = current->next;
//     }

//     // After the loop, close any remaining pipe file descriptors in the parent
//     if (prev_pipe_fd[0] != -1)
//         close(prev_pipe_fd[0]);
//     if (prev_pipe_fd[1] != -1)
//         close(prev_pipe_fd[1]);

//     // Wait for all child processes to finish
//     while (wait(&status) > 0)
//     {
//         if (WIFEXITED(status))
//             mini->exitcode = WEXITSTATUS(status);
//         else
//             mini->exitcode = 1;
//     }

//     // Restore original stdin and stdout
//     dup2(saved_stdin, STDIN_FILENO);
//     dup2(saved_stdout, STDOUT_FILENO);
//     close(saved_stdin);
//     close(saved_stdout);
// }

#include "minishell.h"

bool is_builtin(const char *cmd) {
    return (strcmp(cmd, "echo") == 0 ||
            strcmp(cmd, "cd") == 0 ||
            strcmp(cmd, "pwd") == 0 ||
            strcmp(cmd, "export") == 0 ||
            strcmp(cmd, "unset") == 0 ||
            strcmp(cmd, "env") == 0 ||
            strcmp(cmd, "exit") == 0);
}

void execute_commands(t_mini *mini)
{
    t_commands *current = mini->commands;
    int prev_pipe_fd[2] = {-1, -1};
    pid_t pid;
    int status;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    bool has_pipelines = false;
    t_commands *temp = current;
    while (temp != NULL) {
        if (temp->is_pipe)
            has_pipelines = true;
        temp = temp->next;
    }

    while (current != NULL)
    {
        int pipe_fd[2] = {-1, -1};
        bool current_is_builtin = is_builtin(current->cmds[0]);
        bool execute_in_parent = false;

        // Determine if we should execute this command in the parent
        // Criteria:
        // - It's a built-in
        // - It's the only command (no pipelines)
        if (current_is_builtin && !has_pipelines)
            execute_in_parent = true;

        // If the current command is followed by a pipe, create a new pipe
        if (current->is_pipe)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                mini->exitcode = 1;
                return;
            }
        }

        if (execute_in_parent)
        {
            // Execute built-in in the parent process
            // Handle input from previous pipe if exists
            if (prev_pipe_fd[0] != -1)
            {
                if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
                {
                    perror("dup2 prev_pipe_fd[0]");
                    // Continue to next command or handle error
                }
                close(prev_pipe_fd[0]);
                prev_pipe_fd[0] = -1;
            }

            // Handle output to current pipe if exists
            if (current->is_pipe)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 pipe_fd[1]");
                    // Continue to next command or handle error
                }
                close(pipe_fd[1]);
                pipe_fd[1] = -1;
            }

            handle_builtin_redirections(current);
            execute_builtin(current, mini);
            restore_builtin_redirections(current);

            // If 'exit' was executed, the shell will terminate
            if (strcmp(current->cmds[0], "exit") == 0)
                return; // 'exit' will have already terminated the shell

            // After executing in parent, continue to next command
        }
        else
        {
            // Fork a child process for the current command
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                mini->exitcode = 1;
                return;
            }

            if (pid == 0)
            {
                // In child process

                // If there's a previous pipe, set it as stdin
                if (prev_pipe_fd[0] != -1)
                {
                    if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
                    {
                        perror("dup2 prev_pipe_fd[0]");
                        exit(EXIT_FAILURE);
                    }
                }

                // If there's a current pipe, set its write end as stdout
                if (current->is_pipe)
                {
                    if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                    {
                        perror("dup2 pipe_fd[1]");
                        exit(EXIT_FAILURE);
                    }
                }

                // Close unused file descriptors in the child
                if (prev_pipe_fd[0] != -1)
                {
                    close(prev_pipe_fd[0]);
                }
                if (prev_pipe_fd[1] != -1)
                {
                    close(prev_pipe_fd[1]);
                }
                if (current->is_pipe)
                {
                    close(pipe_fd[0]);
                    close(pipe_fd[1]);
                }

                if (current_is_builtin)
                {
                    // Execute built-in in child
                    handle_builtin_redirections(current);
                    execute_builtin(current, mini);
                    restore_builtin_redirections(current);
                    exit(mini->exitcode);
                }
                else
                {
                    // Execute external command
                    char *cmd_path = find_command_path(current->cmds[0], mini);
                    if (!cmd_path)
                    {
                        fprintf(stderr, "%s: command not found\n", current->cmds[0]);
                        exit(127);
                    }

                    // Handle heredoc if present
                    if (current->heredoc)
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

                    // Handle input redirection
                    if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
                    {
                        if (dup2(current->fd_in, STDIN_FILENO) == -1)
                        {
                            perror("dup2 fd_in");
                            exit(EXIT_FAILURE);
                        }
                        close(current->fd_in);
                    }

                    // Handle output redirection
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
            }
            else
            {
                // In parent process

                // Close the write end of the previous pipe as it's no longer needed
                if (prev_pipe_fd[1] != -1)
                    close(prev_pipe_fd[1]);

                // Close the read end of the previous pipe as it's no longer needed
                if (prev_pipe_fd[0] != -1)
                    close(prev_pipe_fd[0]);

                // Update prev_pipe_fd to the current pipe_fd for the next iteration
                prev_pipe_fd[0] = pipe_fd[0];
                prev_pipe_fd[1] = pipe_fd[1];
            }
        }

        current = current->next;
    }

    // After the loop, close any remaining pipe file descriptors in the parent
    if (prev_pipe_fd[0] != -1)
        close(prev_pipe_fd[0]);
    if (prev_pipe_fd[1] != -1)
        close(prev_pipe_fd[1]);

    // Wait for all child processes to finish
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            mini->exitcode = WEXITSTATUS(status);
        else
            mini->exitcode = 1;
    }

    // Restore original stdin and stdout
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}



// void	execute_commands(t_mini *mini)
// {
// 	t_commands		*current;
// 	pid_t			pid;
// 	int				status;
// 	char			*cmd_path;

// 	current = mini->commands;
// 	while (current != NULL)
// 	{
// 		if (current->cmds == NULL || current->cmds[0] == NULL)
// 		{
// 			current = current->next;
// 			continue;
// 		}
// 		if (current->heredoc)
// 		{
// 			handle_heredoc(current);
// 			if (current->fd_in == -1)
// 			{
// 				mini->exitcode = 1;
// 				current = current->next;
// 				continue;
// 			}
			
// 		}
// 		if (strcmp(current->cmds[0], "echo") == 0 ||
// 			strcmp(current->cmds[0], "cd") == 0 ||
// 			strcmp(current->cmds[0], "pwd") == 0 ||
// 			strcmp(current->cmds[0], "export") == 0 ||
// 			strcmp(current->cmds[0], "unset") == 0 ||
// 			strcmp(current->cmds[0], "env") == 0 ||
// 			strcmp(current->cmds[0], "exit") == 0)
// 		{
// 			handle_builtin_redirections(current);
// 			execute_builtin(current, mini);
// 			restore_builtin_redirections(current);
// 		}
// 		else
// 		{
// 			cmd_path = find_command_path(current->cmds[0], mini);
// 			if (!cmd_path)
// 			{
// 				fprintf(stderr, "%s: command not found\n", current->cmds[0]);
// 				mini->exitcode = 127;
// 				current = current->next;
// 				continue;
// 			}
// 			pid = fork();
// 			if (pid == -1)
// 			{
// 				perror("fork");
// 				mini->exitcode = 1;
// 				ft_gc_free(cmd_path);
// 				return;
// 			}
// 			if (pid == 0)
// 			{
// 				if (current->fd_in != STDIN_FILENO && current->fd_in > 0)
// 				{
// 					if (dup2(current->fd_in, STDIN_FILENO) == -1)
// 					{
// 						perror("dup2 fd_in");
// 						exit(EXIT_FAILURE);
// 					}
// 					close(current->fd_in);
// 				}
// 				if (current->fd_out != STDOUT_FILENO && current->fd_out > 0)
// 				{
// 					if (dup2(current->fd_out, STDOUT_FILENO) == -1)
// 					{
// 						perror("dup2 fd_out");
// 						exit(EXIT_FAILURE);
// 					}
// 					close(current->fd_out);
// 				}
// 				if (execve(cmd_path, current->cmds, mini->envp) == -1)
// 				{
// 					fprintf(stderr, "%s: %s\n", current->cmds[0], strerror(errno));
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 			else
// 			{
// 				waitpid(pid, &status, 0);
// 				if (WIFEXITED(status))
// 					mini->exitcode = WEXITSTATUS(status);
// 				else
// 					mini->exitcode = 1;
// 			}
// 			ft_gc_free(cmd_path);
// 		}
// 		current = current->next;
// 	}
// }
