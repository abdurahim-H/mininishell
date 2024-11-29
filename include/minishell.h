
#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <string.h>

//parsing
void		parse_init(t_mini *mini, char *prompt);
void		createPrompt(t_mini *mini, char *prompt);

//token
Token		*createToken();
int			getOutput(t_mini *mini, Token *token);
int			getInput(t_mini *mini, Token *token);
int			getEnd(t_mini *mini, Token *token);
int			get_pipe(t_mini *mini, Token *token);
int			get_cmd(t_mini *mini, Token *token);
void		printTokens(Token *head);
void		clearTokens(t_mini *mini);
char		*handleDolar(t_mini *mini, Prompt *prompt);

//utils
char		*ft_char_join(char *s1, char c);
int			isToken(char c);
char		*findType(int type);
char		indexc(t_mini *mini);
char		*get_heredoc(char *stop);
void		skip_white_space(Prompt *prompt);
char		*handle_quetos(t_mini *mini, Prompt *prompt);
char		*giveSubstr(char *str, int start, int end);
void		syntaxError(t_mini *mini, char *c);

//commands
t_commands	*createCommands();
int			fillCommands(t_mini *mini, t_commands *newCmd, Token *token);
void		printCmds(t_commands *head);

//fd
int			inOpener(char *name);
int			outOpener(char *name);
int			outApendOpener(char *name);

//free
void		freeArr(char **arr);
char		**ft_realloc_char(char **ptr, int j);
void		clear_cmds(t_commands *cmds);

//execution
void		execute_echo(t_commands *current, t_mini *mini);
void		execute_exit(t_commands *current, t_mini *mini);
void		execute_cd(t_commands *current, t_mini *mini);
void		execute_pwd(t_commands *current, t_mini *mini);
void		execute_commands(t_mini *mini);
char		*ft_getenv(t_mini *mini, const char *name);
int			ft_setenv(t_mini *mini, const char *name, const char *value);
int			find_env_index(char **envp, const char *name);
int			is_valid_identifier(const char *key);
void		remove_env_var(t_mini *mini, const char *var_name);
void		execute_unset(t_commands *current, t_mini *mini);
void		execute_export(t_commands *current, t_mini *mini);
void		execute_env(t_commands *current, t_mini *mini);
// bool	handle_heredoc(t_mini *mini, t_commands *cmd, Token *token);
void	handle_heredoc(t_commands *cmd);
// void		handle_heredoc(t_commands *cmd);
void		restore_builtin_redirections(t_commands *current);
void		handle_builtin_redirections(t_commands *current);
char		*find_command_path(const char *cmd, t_mini *mini);
void		setup_signal_handlers(void);
void		execute_builtin(t_commands *current, t_mini *mini);
bool		is_builtin(const char *cmd);

//test - did not worked for now
// Helper function prototypes
size_t	count_words(const char *s, char delimiter);
char	**allocate_split_result(size_t count);
bool	populate_split_result(char **result, const char *s, char delimiter);
// Helper function prototypes
char	*get_path_direct_command(const char *cmd);
char	*construct_full_path(const char *dir, const char *cmd);
char	*search_in_paths(t_mini *mini, const char *cmd);
char	**get_split_path(t_mini *mini);
char	*find_executable_in_dirs(char **dirs, const char *cmd);


#endif
