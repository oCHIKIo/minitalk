NAME = libftprintf.a
CC = cc
ARCHIVE = ar rcs
FLAGS = -Wall -Wextra -Werror

SRC = ./ft_printf.c ./ft_putchar.c ./ft_putnbr.c ./ft_putstr.c ./ft_put_ptr.c ./ft_put_hexa.c ./ft_unsigned_num.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(ARCHIVE) $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY : clean 