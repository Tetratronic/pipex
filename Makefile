NAME = pipex
BONUS = pipex_bonus
SRCS = main.c initialize.c utils.c cleaners.c quotes_handler.c
BONUS_SRCS = bonus/main_bonus.c initialize.c utils.c cleaners.c quotes_handler.c
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
CC = cc
HEADERS = pipex.h libft/libft.h
BONUS_HEADERS = pipex.h bonus/pipex_bonus.h libft/libft.h
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS)  -I. -c $< -o $@

bonus/%.o: bonus/%.c $(BONUS_HEADERS)
	$(CC) $(CFLAGS) -I. -Ibonus -c $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(OBJS) $(CFLAGS) -Llibft -lft -o $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)


$(BONUS): $(LIBFT) $(BONUS_OBJS) $(BONUS_HEADERS)
	$(CC) $(BONUS_OBJS) $(CFLAGS) -Llibft -lft -o $(BONUS)

bonus: $(BONUS)

clean:
	make clean -C libft/
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME) $(BONUS)

re: clean fclean all bonus
