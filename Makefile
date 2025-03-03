NAME = pipex
SRCS = main.c initialize.c fdutils.c
OBJS = $(SRCS:%.c=%.o)
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
CC = cc
HEADERS = pipex.h
CFLAGS = -Wall -Wextra -Werror -g 

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS)  -I. -c $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(OBJS) $(CFLAGS) -Llibft -lft -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

bonus: all

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all bonus
