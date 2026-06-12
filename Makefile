NAME = xcution

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = minishell_lists.c \
			check_in_out_redir.c \
			env_converter_ll_to_array.c \
			execution.c \
			execution_utils.c \
			execve_preparation.c \
			heredoc_exec.c \
			heredoc_exec_utils.c

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g 
INCLUDE = -Iinclude -I$(LIBFT_DIR)/include

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
