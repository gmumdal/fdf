CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework Appkit 
NAME = fdf
NAME_B = fdf_bonus
SRCS = 	map.c map_utils.c print_map.c \
		print_map_utils.c fdf.c parallel.c
SRCS_B = map_bonus.c map_utils_bonus.c print_map_bonus.c \
		print_map_utils_bonus.c fdf_bonus.c parallel_bonus.c
LIBFT_DIR = libft
LIBFT = -Ilibft -Llibft -lft

all : $(NAME)

$(NAME) : $(SRCS)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(MLX) $(SRCS) -o $(NAME) $(LIBFT)

bonus : $(NAME_B)

$(NAME_B) : $(SRCS_B)
	make -sC $(LIBFT_DIR) all
	$(CC) $(CFLAGS) $(MLX) $(SRCS_B) -o $(NAME_B) $(LIBFT)

clean :
	make -sC $(LIBFT_DIR) fclean

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)

re : fclean all

.PHONY : all bonus clean fclean re
