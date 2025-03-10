NAME = pipex
BONUS = pipex_bonus
SRCS = main.c utils/initialize.c utils/utils.c utils/memory_mgmt.c utils/quotes_handler.c
BONUS_SRCS = bonus/main_bonus.c bonus/heredoc_io_bonus.c bonus/gnl_bonus/get_next_line.c bonus/gnl_bonus/get_next_line_utils.c bonus/utils_bonus/initialize_bonus.c bonus/utils_bonus/utils_bonus.c bonus/utils_bonus/memory_mgmt_bonus.c bonus/utils_bonus/quotes_handler_bonus.c
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)
LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
CC = cc
HEADERS = pipex.h libft/libft.h utils/utils.h
BONUS_HEADERS = bonus/utils_bonus/utils_bonus.h bonus/pipex_bonus.h bonus/gnl_bonus/get_next_line.h libft/libft.h
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS)  -I. -Iutils -c $< -o $@

bonus/%.o: bonus/%.c $(BONUS_HEADERS)
	$(CC) $(CFLAGS) -I. -Iutils -Ibonus -c $< -o $@

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
