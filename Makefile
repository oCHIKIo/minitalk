CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
CLIENT_SRCS = client.c client_utils.c
SERVER_SRCS = server.c
CLIENT_BONUS_SRCS = bonus/client_bonus.c bonus/client_bonus_utils.c
SERVER_BONUS_SRCS = bonus/server_bonus.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
LIBFT_PATH = not_your_libft
PRINTF_PATH = not_your_printf
LIBFT = $(LIBFT_PATH)/libft.a
PRINTF = $(PRINTF_PATH)/libftprintf.a
INCLUDES = -I. -I$(LIBFT_PATH) -I$(PRINTF_PATH)

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(PRINTF):
	@make -s -C $(PRINTF_PATH)

$(SERVER): $(SERVER_OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(SERVER_OBJS) -L$(LIBFT_PATH) -L$(PRINTF_PATH) -lft -lftprintf -o $(SERVER)

$(CLIENT): $(CLIENT_OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT_OBJS) -L$(LIBFT_PATH) -L$(PRINTF_PATH) -lft -lftprintf -o $(CLIENT)

$(SERVER_BONUS): $(SERVER_BONUS_OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) -L$(LIBFT_PATH) -L$(PRINTF_PATH) -lft -lftprintf -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) -L$(LIBFT_PATH) -L$(PRINTF_PATH) -lft -lftprintf -o $(CLIENT_BONUS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -s -C $(LIBFT_PATH) clean
	@make -s -C $(PRINTF_PATH) clean
	@rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_BONUS_OBJS) $(SERVER_BONUS_OBJS)

fclean: clean
	@make -s -C $(LIBFT_PATH) fclean
	@make -s -C $(PRINTF_PATH) fclean
	@rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re