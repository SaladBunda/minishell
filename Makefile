CC = cc
FLAGS = -Wall -Wextra -Werror
SRCS_PARS = ./srcs/parsing/parsing.c \
./srcs/parsing/ds.c \
./srcs/parsing/handlers.c \
./srcs/parsing/brackets.c \
./srcs/parsing/lexer_utils.c \
./srcs/parsing/joiner.c \
./srcs/parsing/env_handlers.c \
./srcs/parsing/free.c \
./srcs/parsing/subst_utils.c \
./srcs/parsing/family.c \
./srcs/builtins/echo.c \
./srcs/builtins/pwd.c \
./srcs/builtins/cd.c \
./srcs/builtins/variables.c \
./srcs/builtins/exit.c \
./srcs/parsing/syntax.c \
./srcs/parsing/organizer.c \
./srcs/parsing/executionner.c \
./srcs/parsing/command.c \
./srcs/parsing/redirs.c \
./srcs/parsing/redirs_utils.c \
./srcs/execution/handle_pipes.c \
./srcs/execution/signals.c \
./srcs/execution/files_utils.c \
./srcs/execution/heredoc_utils.c \
./srcs/execution/utilities.c \
./srcs/parsing/paths.c \
./srcs/parsing/env_utils.c \
./srcs/parsing/joiner_utils.c \
./srcs/parsing/organizer_utils.c \
./srcs/parsing/free_ll.c \
./srcs/parsing/free_nodes.c \
./srcs/builtins/exit_utils.c \
./srcs/builtins/cd_util.c
SRCS_EXEC = ./srcs/execution/execution.c
ENTRY = minishell.c
INCLUDE = ./include/
PARS_OBJS = $(SRCS_PARS:.c=.o)
EXEC_OBJS = $(SRCS_EXEC:.c=.o)
LIBFT = libft.a
NAME = minishell
# FS=-fsanitize=address -g
#./srcs/parsing/wildcards.c

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(ENTRY) $(LIBFT) $(PARS_OBJS) $(EXEC_OBJS)
	$(CC) $(FLAGS) $(FS) -I$(INCLUDE) -I./libft $(PARS_OBJS) $(EXEC_OBJS) $(ENTRY) -L. -lft -L./lib -lreadline -o $(NAME)

clean:
	rm -rf $(PARS_OBJS) $(EXEC_OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME) $(LIBFT)
	make fclean -C libft

re: fclean all
