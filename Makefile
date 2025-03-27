NAME        = minitalk
SERVER      = server
CLIENT      = client
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -Inot_your_printf/includes -Inot_your_libft

SRC_SERVER  = server.c
SRC_CLIENT  = client.c
SRC_LIBFT   = not_your_libft/ft_atoi.c not_your_libft/ft_isdigit.c not_your_libft/ft_strlen.c

PRINTF_DIR  = not_your_printf
PRINTF_LIB  = $(PRINTF_DIR)/libftprintf.a

all: $(SERVER) $(CLIENT)

$(PRINTF_LIB):
	@make -sC $(PRINTF_DIR)

$(SERVER): $(SRC_SERVER) $(SRC_LIBFT) $(PRINTF_LIB)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf

$(CLIENT): $(SRC_CLIENT) $(SRC_LIBFT) $(PRINTF_LIB)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -L$(PRINTF_DIR) -lftprintf

clean:
	@make -sC $(PRINTF_DIR) clean
	@rm -f $(SRC_LIBFT:.c=.o)

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@make -sC $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re