
#ifndef STRUCTS_H
#define STRUCTS_H

# include <sys/wait.h>
# include <stdbool.h>

typedef enum
{
	COMMAND,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	END,
	INVALID
} TokenType;

typedef struct Token
{
	TokenType		type;
	char			*text;
	struct Token	*next;
} Token;

typedef struct
{
	char	*prom;
	int		i;
} Prompt;

typedef struct s_commands
{
	char				**cmds;
	int					ind;
	int					fd_in;
	int					fd_out;
	int					saved_stdin;
	int					saved_stdout;
	char				*heredoc;
	bool				is_pipe;
	struct s_commands	*next;
} t_commands;

typedef struct s_mini
{
	Prompt		*prompt;
	int			exitcode;
	Token		*tokens;
	t_commands	*commands;
	char		**envp;
} t_mini;

#endif
