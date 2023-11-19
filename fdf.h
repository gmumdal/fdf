/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:23:39 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/19 16:15:53 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"

# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define BIG		35
# define SMALL		46
# define TURN_R		15
# define TURN_L		37
# define SIGHT		1
# define ESC		53
# define KEYPRESS	2

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		endian;
	void	*mlx;
	void	*win;
	int		**imap;
	int		**color;
	int		size;
	int		len;
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		zoom;
	int		sight;
	double	angle;
}	t_data;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

void	make_map(char *file, t_data *data);
void	ft_split_int(int i, char *tmp, t_data *data);
int		file_check(char *file, char *check);
int		check_wordnum(char *s);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_map(t_data *data);
void	print_line(t_data *data, int flag);
void	draw_line(t_data *data, t_point *tpos, int ncolor);
int		color_check(char **tmp);
int		hexa_index(char c, char *lower, char *upper);
int		check_flag(t_point *tpos, t_data *data, int flag, t_point angles);
int		ft_key_press(int keycode, t_data *data);
int		get_trgb(int trgb, int flag);
int		create_trgb(int t, int r, int g, int b);
int		grad_rgb(double ratio, int color, int ncolor);
void	init_map(t_data *data);
void	check_keycode(int keycode, t_data *data);
void	check_angle(t_data *data, t_point *angles, t_point *start);
void	print_line_para(t_data *data, int flag);
void	check_start(t_data *data, t_point *start);

#endif
