/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:44:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 22:05:45 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	print_map(t_data *img, t_map *map)
{
	map->pos[0] = 0;
	while (map->pos[0] < map->len)
	{
		map->pos[1] = 0;
		while (map->pos[1] < map->size)
		{
			if (map->pos[0] < map->len - 1)
				print_line(img, map, 0);
			if (map->pos[1] < map->size - 1)
				print_line(img, map, 1);
			map->pos[1]++;
		}
		map->pos[0]++;
	}
}

void	print_line(t_data *img, t_map *map, int flag)
{
	t_point	tpos[2];
	double	grad;
	int		zoom;

	zoom = 1;
	if (map->size < 100 || map->len < 100)
		zoom = 25;
	tpos[0].x = 500 + ((map->pos[0] * cos(M_PI / 6)
				- map->pos[1] * sin(M_PI / 3)) * zoom);
	tpos[0].y = 500 + ((map->pos[0] * sin(M_PI / 6)
				+ map->pos[1] * cos(M_PI / 3)) * zoom);
	grad = check_flag(tpos, zoom, map, flag);
	tpos[0].y -= 2 * map->imap[map->pos[1]][map->pos[0]];
	draw_line(img, tpos, grad, map);
}

double	check_flag(t_point *tpos, int zoom, t_map *map, int flag)
{
	double	grad;

	if (flag == 0)
	{
		tpos[1].x = tpos[0].x + cos(M_PI / 6) * zoom;
		tpos[1].y = tpos[0].y + sin(M_PI / 6) * zoom
			- 2 * map->imap[map->pos[1]][map->pos[0] + 1];
		grad = map->color[map->pos[1]][map->pos[0] + 1]
			- map->color[map->pos[1]][map->pos[0]];
	}
	else
	{
		tpos[1].x = tpos[0].x - sin(M_PI / 3) * zoom;
		tpos[1].y = tpos[0].y + cos(M_PI / 3) * zoom
			- 2 * map->imap[map->pos[1] + 1][map->pos[0]];
		grad = map->color[map->pos[1] + 1][map->pos[0]]
			- map->color[map->pos[1]][map->pos[0]];
	}
	return (grad);
}

void	draw_line(t_data *img, t_point *tpos, double grad, t_map *map)
{
	t_point	dpos;
	double	step;
	double	color;
	double	i;

	color = map->color[map->pos[1]][map->pos[0]];
	dpos.x = tpos[1].x - tpos[0].x;
	dpos.y = tpos[1].y - tpos[0].y;
	if (fabs(dpos.x) > fabs(dpos.y))
		step = fabs(dpos.x);
	else
		step = fabs(dpos.y);
	dpos.x = dpos.x / step;
	dpos.y = dpos.y / step;
	grad = grad / step;
	i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(img, round(tpos[0].x), round(tpos[0].y), round(color));
		tpos[0].x = tpos[0].x + dpos.x;
		tpos[0].y = tpos[0].y + dpos.y;
		color = color + grad;
		i++;
	}
}
