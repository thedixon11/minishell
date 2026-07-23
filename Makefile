NAME = xcution

XPAND_DIR = src_xpand
EXEC_DIR = src_exec
TEST_DIR = src_test
XPAND_OBJ_DIR = obj_xpand
EXEC_OBJ_DIR = obj_exec
TEST_OBJ_DIR = obj_test

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

EXEC =	child_process.c \
		classic_execution.c \
		close_fd_utils.c \
		env_converter_ll_to_array.c \
		execute_cmds.c \
		execution_start.c \
		execve_preparation.c \
		execve_preparation_utils.c \
		free_utils.c \
		ft_error.c \
		heredoc_exec.c \
		heredoc_exec_utils.c \
		manage_redirections.c \
		some_utils.c \
		write_on_fd.c

XPAND = val_manager.c \
				val_manager_utils.c \
				quote_manager.c \
				env_var_manager.c \
				dollar_manager.c

TEST = minishell_lists15.c

XPAND := $(addprefix $(XPAND_DIR)/,$(XPAND))
EXEC := $(addprefix $(EXEC_DIR)/,$(EXEC))
TEST := $(addprefix $(TEST_DIR)/,$(TEST))

OBJS_XPAND := $(patsubst $(XPAND_DIR)/%.c,$(XPAND_OBJ_DIR)/%.o,$(XPAND))
OBJS_EXEC := $(patsubst $(EXEC_DIR)/%.c,$(EXEC_OBJ_DIR)/%.o,$(EXEC))
OBJS_TEST := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST))

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
VFLAGS = --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=yes ./xcution
INCLUDE = -I$(EXEC_DIR)/include -I$(XPAND_DIR)/include -I$(LIBFT_DIR)/include

all: $(NAME)

$(NAME): $(OBJS_TEST) $(OBJS_EXEC) $(OBJS_XPAND) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_TEST) $(OBJS_EXEC) $(OBJS_XPAND) $(LIBFT) -o $(NAME)
	clear
	valgrind $(VFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(EXEC_OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(EXEC_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(XPAND_OBJ_DIR)/%.o: $(XPAND_DIR)/%.c
	@mkdir -p $(XPAND_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

ma: $(NAME)
	clear
	valgrind $(VFLAGS)

clean:
	$(RM) -r $(TEST_OBJ_DIR) $(EXEC_OBJ_DIR) $(XPAND_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
