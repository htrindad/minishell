#Files
NAME = minishell

CFLAGS = -Wall -Werror -Wextra -O3

SRC = ./src/free.c ./src/get_env.c ./src/init_ms.c ./src/handle/env_var.c \
	./src/lex/split_shell.c ./src/lex/split_shell_utils.c ./src/lexing.c \
	./src/handle/env_var_utils.c ./src/builtins/ecpeu.c ./src/duplicator.c \
	./src/lexing/split_shell_ops.c ./src/main.c

OBJ_DIR = ./obj
OBJ = $(patsubst $(SRC)/%.c, $(OBJ_DIR)/%.o, $(SRC))

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
$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@clang $(CFLAGS) -c $< -o $@
	@$(eval COUNT=$(shell expr $(words $(shell ls $(OBJ_DIR)/*.o 2>/dev/null)) + 1))
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
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)✗ Objects removed$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW)✗ libs removed$(RESET)"
	@rm -f $(NAME)
	@echo "$(YELLOW)✗ Executable removed$(RESET)"

re: fclean all
