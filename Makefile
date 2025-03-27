NAME        = minitalk
SERVER      = server
CLIENT      = client
BONUS_SERVER = server_bonus
BONUS_CLIENT = client_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -Inot_your_printf/includes -Inot_your_libft

SRC_SERVER  = server.c
SRC_CLIENT  = client.c
BONUS_SRC_SERVER = bonus/server_bonus.c
BONUS_SRC_CLIENT = bonus/client_bonus.c
SRC_LIBFT   = not_your_libft/ft_atoi.c \
              not_your_libft/ft_isdigit.c \
              not_your_libft/ft_strlen.c \
			  not_your_libft/is_valid_pid.c 

OBJ_LIBFT   = $(SRC_LIBFT:.c=.o)

PRINTF_DIR  = not_your_printf
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a
LIBFT       = not_your_libft/libft.a

WOLF        = 🐺
GREEN_WOLF  = \033[1;32m$(WOLF)
RED_WOLF    = \033[1;31m$(WOLF)
YELLOW_WOLF = \033[1;33m$(WOLF)
BLUE_WOLF   = \033[1;34m$(WOLF)
RESET       = \033[0m

# Rules
all: $(SERVER) $(CLIENT)

$(LIBFT): $(OBJ_LIBFT)
	@ar rcs $@ $^

$(PRINTF_LIB):
	@make -sC $(PRINTF_DIR)

$(OBJ_LIBFT): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER): $(SRC_SERVER) $(LIBFT) $(PRINTF_LIB)
	@echo "$(GREEN_WOLF) Compiling server...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf -Lnot_your_libft -lft
	@echo "$(GREEN_WOLF) Server Ready! $(RESET)"

$(CLIENT): $(SRC_CLIENT) $(LIBFT) $(PRINTF_LIB)
	@echo "$(GREEN_WOLF) Compiling client...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf -Lnot_your_libft -lft
	@echo "$(GREEN_WOLF) Client Ready! $(RESET)"

bonus: $(BONUS_SERVER) $(BONUS_CLIENT)

$(BONUS_SERVER): $(BONUS_SRC_SERVER) $(LIBFT) $(PRINTF_LIB)
	@echo "$(GREEN_WOLF) Compiling bonus server...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf -Lnot_your_libft -lft
	@echo "$(GREEN_WOLF) Bonus Server Ready! $(RESET)"

$(BONUS_CLIENT): $(BONUS_SRC_CLIENT) $(LIBFT) $(PRINTF_LIB)
	@echo "$(GREEN_WOLF) Compiling bonus client...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf -Lnot_your_libft -lft
	@echo "$(GREEN_WOLF) Bonus Client Ready! $(RESET)"

clean:
	@echo "$(RED_WOLF) Cleaning object files...$(RESET)"
	@make -sC $(PRINTF_DIR) clean
	@rm -f $(OBJ_LIBFT) $(LIBFT)
	@echo "$(RED_WOLF) Cleaned Successfully! $(RESET)"

fclean: clean
	@echo "$(YELLOW_WOLF) Removing executables...$(RESET)"
	@rm -f $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)
	@echo "$(YELLOW_WOLF) Force Cleaned Successfully! $(RESET)"

re: fclean all
	@echo "$(BLUE_WOLF) Rebuilt Successfully! $(RESET)"

.PHONY: all clean fclean re bonus