NAME = minishell

CFILES = src/minishell.c \
src/validation.c \
src/debug.c \
src/builtins/builtin.c \
src/builtins/cd.c \
src/builtins/echo.c \
src/builtins/exit.c \
src/builtins/export.c \
src/builtins/pwd.c \
src/builtins/unset.c \
src/execution/multiple_utils.c \
src/execution/execution.c \
src/execution/traverse.c \
src/execution/one_pass.c \
src/execution/two_pass.c \
src/execution/commands.c \
src/parsing/ast.c \
src/parsing/ast_env.c \
src/parsing/quotes.c \
src/parsing/cleanup.c \
src/enviroment/env_utils.c \
src/enviroment/env_1.c \
src/enviroment/env_2.c \
utils/exec_utils.c \
utils/parsing.c \
utils/ft_splitms.c \
utils/init.c \
utils/tree.c \
utils/frees.c \
utils/signals.c \
utils/exec_frees.c \
utils/env_frees.c \
utils/parsing_errors.c \
utils/execution_errors.c \

OBJECTS = $(CFILES:.c=.o)

LIBFT_PATH = libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I/opt/vagrant/embedded/include/
CFLAGS += -g3

LINKFLAGS = -L/opt/vagrant/embedded/lib/ -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: subsystems $(NAME)

subsystems:
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJECTS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAGS) $(LINKFLAGS) -o $(NAME)

clean:
	make clean -C libft/
	rm -rf $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
