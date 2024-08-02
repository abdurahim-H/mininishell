
#ifndef STRUCTS_H
#define STRUCTS_H

#include <sys/wait.h>

typedef enum
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	BACKGROUND,
	SEMICOLON,
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

} t_commands;

typedef struct s_mini
{
	Prompt		*prompt;
	int			exitcode;
	Token		*tokens;
	t_commands	commads;
} t_mini;

#endif
