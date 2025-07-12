#Files
NAME = minishell

CFLAGS = -Wall -Werror -Wextra -O3 -D DEBUG=1

SRC = ./src/free.c ./src/get_env.c ./src/init_ms.c ./src/handle/env_var.c \
	./src/lex/split_shell.c ./src/lex/split_shell_utils.c ./src/lexing.c \
	./src/handle/env_var_utils.c ./src/builtins/ecpeu.c ./src/duplicator.c \
	./src/lex/split_shell_ops.c ./src/lex/quoter.c ./src/free_utils.c \
	./src/sig_handler.c ./src/execute/executor.c ./src/execute/executor_utils.c \
	./src/execute/executor_ops.c ./src/builtins/dir.c ./src/builtins/echo.c \
	./src/builtins/export.c ./src/builtins/unset.c ./src/execute/redir.c \
	./src/execute/redir_utils.c ./src/error.c ./src/debug.c ./src/debug2.c \
	./src/execute/redir_utils2.c ./src/execute/comp_env.c ./src/lexing_utils.c \
	./src/get_env_utils.c ./src/main.c ./src/execute/heredoc.c ./src/execute/b_in.c \
	./src/execute/heredoc_utils.c

OBJ_DIR = ./obj
OBJ = $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = ./libs/neo_libft
LIBFT= $(LIBFT_DIR)/neo_libft.a

#Colors
YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

#Progress
TOTAL := $(words $(SRC))

#Compilation
all: $(NAME)

## Create 'obj' dir in case it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

## Compile each .c file into an .o file
$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@
	@$(eval COUNT=$(shell expr $(words $(shell find $(OBJ_DIR) -name '*.o' 2>/dev/null)) + 1))
	@PERCENT=$$(($(COUNT) * 100 / $(TOTAL))); \
	FILLED=$$((PERCENT / 2)); \
	EMPTY=$$((50 - FILLED)); \
	BAR=$$(printf "%0.s█" $$(seq 1 $$FILLED)); \
	SPACES=$$(printf "%0.s " $$(seq 1 $$EMPTY)); \
	printf "\r$(YELLOW)[Compiling]$(RESET) [$${BAR}$${SPACES}] $${PERCENT}%%"

## Compile neo_libft
$(LIBFT):
	@echo "$(YELLOW)compiling neo_libft$(RESET)"
	@make bonus -s -C $(LIBFT_DIR)

## Rule to compile the final executable
$(NAME): $(LIBFT) $(OBJ)
	@echo "\n$(GREEN)[Linking]$(RESET) $@"
	@cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)✔ Build complete!$(RESET)"

# Clean up object files and executable
clean:
	@make clean_bonus -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)✗ Objects removed$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW)✗ libs removed$(RESET)"
	@rm -f $(NAME)
	@echo "$(YELLOW)✗ Executable removed$(RESET)"

re: fclean all
