.SILENT:

COLOUR_DEFAULT = \033[0m
COLOUR_BLACK = \033[0;30m
COLOUR_RED = \033[0;31m
COLOUR_GREEN = \033[0;32m
COLOUR_YELLOW = \033[0;33m
COLOUR_BLUE = \033[0;34m
COLOUR_MAGENTA = \033[0;35m
COLOUR_CYAN = \033[0;36m
COLOUR_WHITE = \033[0;37m
COLOUR_BOLD = \033[1m
COLOUR_UNDERLINE = \033[4m
COLOUR_END = \033[0m

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./include/ -g

SRC_DIR = src
SRC =	main.c \
		parse/parse.c \
		parse/utils.c \
		parse/quetoes.c \
		parse/expand.c \
		parse/token.c \
		parse/utilsToken.c \
		parse/commands.c \
		parse/fileD.c \
		execution/execution.c \
		execution/builtins_00.c \
		execution/builtins_01.c \
		execution/heredoc_00.c \
		execution/path.c \
		execution/signals.c \
		utils/print_utils.c \
		utils/free.c \
		utils/error_msg.c \


OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = minishell

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME) -lreadline
	echo "$(COLOUR_MAGENTA)Minishell compiled successfully!$(COLOUR_END)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/parse
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/execution

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all: $(NAME)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	echo "$(COLOUR_MAGENTA)$(COLOUR_UNDERLINE)Minishell cleaned successfully!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re