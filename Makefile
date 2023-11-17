CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework Appkit 
NAME = fdf
SRCS = get_next_line.c get_next_line_utils.c map.c print_map.c fdf.c map_util.c

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(MLX) $(SRCS) -o $(NAME)

clean :

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
