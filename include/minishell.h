
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
void	parse_init(t_mini *mini, char *prompt);
void	createPrompt(t_mini *mini, char *prompt);
void	get_cmd(t_mini *mini, Token *token);

void	skip_white_space(Prompt *prompt);
char	*handle_quetos(Prompt *prompt);
char	*giveSubstr(char *str, int start, int end);
Token	*createToken();
//utils
char	*ft_char_join(char *s1, char c);
void	printTokens(Token *head);
int		isToken(char c);
char	*findType(int type);





#endif
