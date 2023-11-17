/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:44:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 21:02:56 by hyeongsh         ###   ########.fr       */
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
	double	pos[2][2];
	double	grad;
	int		zoom;

	zoom = 1;
	if (map->size < 100 || map->len < 100)
		zoom = 30;
	pos[0][0] = 500 + ((map->pos[0] * cos(M_PI / 6)
				- map->pos[1] * sin(M_PI / 3)) * zoom);
	pos[0][1] = 500 + ((map->pos[0] * sin(M_PI / 6)
				+ map->pos[1] * cos(M_PI / 3)) * zoom);
	if (flag == 0)
	{
		pos[1][0] = pos[0][0] + cos(M_PI / 6) * zoom;
		pos[1][1] = pos[0][1] + sin(M_PI / 6) * zoom
			- 2 * map->imap[map->pos[1]][map->pos[0] + 1];
		grad = map->color[map->pos[1]][map->pos[0] + 1]
			- map->color[map->pos[1]][map->pos[0]];
	}
	else
	{
		pos[1][0] = pos[0][0] - sin(M_PI / 3) * zoom;
		pos[1][1] = pos[0][1] + cos(M_PI / 3) * zoom
			- 2 * map->imap[map->pos[1] + 1][map->pos[0]];
		grad = map->color[map->pos[1] + 1][map->pos[0]]
			- map->color[map->pos[1]][map->pos[0]];
	}
	pos[0][1] -= 2 * map->imap[map->pos[1]][map->pos[0]];
	draw_line(img, pos, grad, map);
}

void	draw_line(t_data *img, double pos[2][2], double grad, t_map *map)
{
	double	dpos[2];
	double	step;
	double	color;
	double	i;

	color = map->color[map->pos[1]][map->pos[0]];
	dpos[0] = pos[1][0] - pos[0][0];
	dpos[1] = pos[1][1] - pos[0][1];
	if (fabs(dpos[0]) > fabs(dpos[1]))
		step = fabs(dpos[0]);
	else
		step = fabs(dpos[1]);
	dpos[0] = dpos[0] / step;
	dpos[1] = dpos[1] / step;
	grad = grad / step;
	i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(img, round(pos[0][0]), round(pos[0][1]), round(color));
		pos[0][0] = pos[0][0] + dpos[0];
		pos[0][1] = pos[0][1] + dpos[1];
		color = color + grad;
		i++;
	}
}
