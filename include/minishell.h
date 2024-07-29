
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
# include <stdlib.h>
# include <termios.h>
# include <limits.h>


void parse();


#endif
