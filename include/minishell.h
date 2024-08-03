
#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_RESET	"\x1b[0m"

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








#endif
