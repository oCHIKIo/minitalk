CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
NAME = libft.a

SRCS = ft_atoi.c \
       ft_isdigit.c \
       ft_strlen.c \
       is_valid_pid.c

OBJS = $(SRCS:.c=.o)

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re