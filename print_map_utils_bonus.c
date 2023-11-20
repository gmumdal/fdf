/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:30:58 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/20 18:58:51 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	get_trgb(int trgb, int flag)
{
	if (flag == 0)
		return ((trgb & (0xFF000000)) >> 24);
	else if (flag == 1)
		return ((trgb & (0xFF0000)) >> 16);
	else if (flag == 2)
		return ((trgb & (0xFF00)) >> 8);
	else
		return (trgb & 0xFF);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	grad_rgb(double ratio, int color, int ncolor)
{
	int	t;
	int	r;
	int	g;
	int	b;

	if (color == ncolor)
		return (color);
	t = ratio * get_trgb(ncolor, 0) + (1 - ratio) * get_trgb(color, 0) + 0.5;
	r = ratio * get_trgb(ncolor, 1) + (1 - ratio) * get_trgb(color, 1) + 0.5;
	g = ratio * get_trgb(ncolor, 2) + (1 - ratio) * get_trgb(color, 2) + 0.5;
	b = ratio * get_trgb(ncolor, 3) + (1 - ratio) * get_trgb(color, 3) + 0.5;
	return (create_trgb(t, r, g, b));
}

void	check_angle(t_data *data, t_point *angles, t_point *start)
{
	if (data->angle == 0)
	{
		angles->x = M_PI / 6;
		angles->y = M_PI / 3;
		start->y = data->start_y - (data->size * cos(M_PI / 3) * data->zoom);
	}
	if (data->angle == 1)
	{
		angles->x = -M_PI / 6;
		angles->y = -M_PI / 3;
		start->x = data->start_x - (data->len * cos(M_PI / 6) * data->zoom);
	}
	if (data->angle == 2)
	{
		angles->x = M_PI + M_PI / 6;
		angles->y = M_PI + M_PI / 3;
		start->y = data->start_y + (data->size * cos(M_PI / 3) * data->zoom);
	}
	if (data->angle == 3)
	{
		angles->x = M_PI - M_PI / 6;
		angles->y = M_PI - M_PI / 3;
		start->x = data->start_x + (data->len * cos(M_PI / 6) * data->zoom);
	}
}

int	check_flag(t_point *tpos, t_data *data, int flag, t_point angles)
{
	int	ncolor;

	if (flag == 0 || flag == 2)
	{
		tpos[1].x = tpos[0].x + cos(angles.x) * data->zoom;
		tpos[1].y = tpos[0].y + sin(angles.x) * data->zoom
			- data->imap[data->y][data->x + 1] * data->zoom * data->height;
		if (flag == 2)
			tpos[1].y = tpos[0].y + sin(angles.x) * data->zoom;
		ncolor = data->color[data->y][data->x + 1];
	}
	else
	{
		tpos[1].x = tpos[0].x - sin(angles.y) * data->zoom;
		tpos[1].y = tpos[0].y + cos(angles.y) * data->zoom
			- data->imap[data->y + 1][data->x] * data->zoom * data->height;
		if (flag == 3)
			tpos[1].y = tpos[0].y + cos(angles.y) * data->zoom;
		ncolor = data->color[data->y + 1][data->x];
	}
	return (ncolor);
}
