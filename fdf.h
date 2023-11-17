/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:23:39 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 20:57:54 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "get_next_line.h"
//# include "libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_map
{
	int	**imap;
	int	**color;
	int	size;
	int	len;
	int	pos[2];
}	t_map;

void	make_map(char *file, t_map *mapinfo);
void	ft_split_int(int i, char *tmp, t_map *map);
int		check_wordnum(char *s);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_map(t_data *img, t_map *map);
void	print_line(t_data *img, t_map *map, int flag);
void	draw_line(t_data *img, double pos[2][2], double grad, t_map *map);
int		color_check(char **tmp);
int		hexa_index(char c, char *lower, char *upper);

#endif
