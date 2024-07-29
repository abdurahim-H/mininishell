
#ifndef MINISHELL_H
# define MINISHELL_H

# define ANSI_COLOR_RESET	"\x1b[0m"

# include "structs.h"
# include "ft_gc.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <limits.h>


//parsing
void	parse_init(t_mini *mini, char *prompt);

char	*ft_strdup_gb(const char *s1);
void	createPrompt(t_mini *mini, char *prompt);

//utils




#endif
