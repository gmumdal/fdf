CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework Appkit 
NAME = fdf
SRCS = get_next_line.c get_next_line_utils.c map.c map_utils.c print_map.c print_map_utils.c fdf.c parallel.c
all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(MLX) $(SRCS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
