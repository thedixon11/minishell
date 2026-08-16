NAME = minishell

PARSING_DIR = src_parsing
XPAND_DIR = src_xpand
EXEC_DIR = src_exec
BUILTIN_DIR = src_builtin
TEST_DIR = src_test
HEREDOC_DIR = src_heredoc
ERRORS_DIR = src_errors
PARSING_OBJ_DIR = obj_parsing
XPAND_OBJ_DIR = obj_xpand
EXEC_OBJ_DIR = obj_exec
BUILTIN_OBJ_DIR = obj_builtin
TEST_OBJ_DIR = obj_test
HEREDOC_OBJ_DIR = obj_heredoc
ERRORS_OBJ_DIR = obj_errors

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

EXEC =	child_process.c \
		classic_execution.c \
		env_converter_ll_to_array.c \
		execute_cmds.c \
		execution_start.c \
		execve_preparation.c \
		execve_preparation_utils.c \
		manage_redirections.c \
		some_utils.c \
		no_command_process.c

XPAND = val_manager.c \
		val_manager_utils.c \
		quote_manager.c \
		env_var_manager.c \
		dollar_manager.c \
		dollar_manager_utils.c

HEREDOC = heredoc_exec.c \
		  heredoc_exec_utils.c \
		  write_on_fd.c \
			delimiter_manager.c

ERRORS = ft_error.c \
		 free_utils.c \
		 close_fd_utils.c

BUILTIN = ft_export.c \
		  ft_export_print.c \
		  ft_export_utils.c \
		  ft_export_utils_two.c \
		  ft_echo.c \
		  ft_cd.c \
		  ft_cd_utils.c \
		  ft_env.c \
		  ft_exit.c \
		  ft_unset.c \
		  ft_pwd.c \
		  builtin_exec.c

PARSING = minishell.c \
		  node_utils.c \
		  parse_utils.c \
		  to_parse.c \
		  to_token.c \
		  to_token_utils.c \
		  create_env.c \
		  is_there_env.c

PARSING := $(addprefix $(PARSING_DIR)/,$(PARSING))
XPAND := $(addprefix $(XPAND_DIR)/,$(XPAND))
EXEC := $(addprefix $(EXEC_DIR)/,$(EXEC))
BUILTIN := $(addprefix $(BUILTIN_DIR)/,$(BUILTIN))
TEST := $(addprefix $(TEST_DIR)/,$(TEST))
HEREDOC := $(addprefix $(HEREDOC_DIR)/,$(HEREDOC))
ERRORS := $(addprefix $(ERRORS_DIR)/,$(ERRORS))

OBJS_PARSING := $(patsubst $(PARSING_DIR)/%.c,$(PARSING_OBJ_DIR)/%.o,$(PARSING))
OBJS_XPAND := $(patsubst $(XPAND_DIR)/%.c,$(XPAND_OBJ_DIR)/%.o,$(XPAND))
OBJS_EXEC := $(patsubst $(EXEC_DIR)/%.c,$(EXEC_OBJ_DIR)/%.o,$(EXEC))
OBJS_BUILTIN := $(patsubst $(BUILTIN_DIR)/%.c,$(BUILTIN_OBJ_DIR)/%.o,$(BUILTIN))
OBJS_TEST := $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST))
OBJS_HEREDOC := $(patsubst $(HEREDOC_DIR)/%.c,$(HEREDOC_OBJ_DIR)/%.o,$(HEREDOC))
OBJS_ERRORS := $(patsubst $(ERRORS_DIR)/%.c,$(ERRORS_OBJ_DIR)/%.o,$(ERRORS))

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
VFLAGS = --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp
INCLUDE = -I$(PARSING_DIR)/include -I$(EXEC_DIR)/include -I$(XPAND_DIR)/include -I$(BUILTIN_DIR)/include -I$(HEREDOC_DIR)/include -I$(ERRORS_DIR)/include -I$(LIBFT_DIR)/include

all: $(NAME)

$(NAME): $(OBJS_PARSING) $(OBJS_TEST) $(OBJS_EXEC) $(OBJS_XPAND) $(OBJS_BUILTIN) $(OBJS_HEREDOC) $(OBJS_ERRORS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_PARSING) $(OBJS_TEST) $(OBJS_EXEC) $(OBJS_XPAND) $(OBJS_BUILTIN) $(OBJS_HEREDOC) $(OBJS_ERRORS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(EXEC_OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(EXEC_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(XPAND_OBJ_DIR)/%.o: $(XPAND_DIR)/%.c
	@mkdir -p $(XPAND_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILTIN_OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c
	@mkdir -p $(BUILTIN_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(HEREDOC_OBJ_DIR)/%.o: $(HEREDOC_DIR)/%.c
	@mkdir -p $(HEREDOC_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(ERRORS_OBJ_DIR)/%.o: $(ERRORS_DIR)/%.c
	@mkdir -p $(ERRORS_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(PARSING_OBJ_DIR)/%.o: $(PARSING_DIR)/%.c
	@mkdir -p $(PARSING_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -r $(TEST_OBJ_DIR) $(EXEC_OBJ_DIR) $(XPAND_OBJ_DIR) $(BUILTIN_OBJ_DIR) $(HEREDOC_OBJ_DIR) $(ERRORS_OBJ_DIR) $(PARSING_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
	@clear
	@#valgrind $(VFLAGS) ./$(NAME)

.PHONY: all clean fclean re
