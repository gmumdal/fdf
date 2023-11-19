CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework Appkit 
NAME = fdf
NAME_B = fdf_bonus
SRCS = get_next_line.c get_next_line_utils.c map.c \
		map_utils.c print_map.c print_map_utils.c \
		fdf.c parallel.c
SRCS_B = get_next_line_bonus.c get_next_line_utils_bonus.c \
		map_bonus.c map_utils_bonus.c print_map_bonus.c \
		print_map_utils_bonus.c fdf_bonus.c parallel_bonus.c

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(MLX) $(SRCS) -o $(NAME)

bonus : $(NAME_B)

$(NAME_B) : $(SRCS_B)
	$(CC) $(CFLAGS) $(MLX) $(SRCS_B) -o $(NAME_B)

clean :

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)

re : fclean all

.PHONY : all bonus clean fclean re
