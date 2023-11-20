/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:44:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/20 18:56:46 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	print_map(t_data *data)
{
	data->x = 0;
	while (data->x < data->len)
	{
		data->y = 0;
		while (data->y < data->size)
		{
			if (data->x < data->len - 1)
			{
				if (data->sight == 0)
					print_line(data, 0);
				else
					print_line_para(data, 2);
			}
			if (data->y < data->size - 1)
			{
				if (data->sight == 0)
					print_line(data, 1);
				else
					print_line_para(data, 3);
			}
			data->y++;
		}
		data->x++;
	}
}

void	print_line(t_data *data, int flag)
{
	t_point	tpos[2];
	t_point	angles;
	t_point	start;
	int		ncolor;

	start.x = data->start_x;
	start.y = data->start_y;
	check_angle(data, &angles, &start);
	tpos[0].x = start.x + ((data->x * cos(angles.x)
				- data->y * sin(angles.y)) * data->zoom);
	tpos[0].y = start.y + ((data->x * sin(angles.x)
				+ data->y * cos(angles.y)) * data->zoom);
	ncolor = check_flag(tpos, data, flag, angles);
	tpos[0].y -= (data->imap[data->y][data->x] * data->height) * data->zoom;
	if (tpos[0].x > 1000 || tpos[0].y > 1000
		|| tpos[1].x > 1000 || tpos[1].y > 1000
		|| tpos[0].x < 0 || tpos[0].y < 0
		|| tpos[1].x < 0 || tpos[1].y < 0)
		return ;
	draw_line(data, tpos, ncolor);
}

void	draw_line(t_data *data, t_point *tpos, int ncolor)
{
	t_point	dpos;
	int		step;
	int		i;
	int		color;

	color = data->color[data->y][data->x];
	dpos.x = tpos[1].x - tpos[0].x;
	dpos.y = tpos[1].y - tpos[0].y;
	if (fabs(dpos.x) > fabs(dpos.y))
		step = fabs(dpos.x);
	else
		step = fabs(dpos.y);
	dpos.x = dpos.x / step;
	dpos.y = dpos.y / step;
	i = 0;
	while (i <= step)
	{
		my_mlx_pixel_put(data, tpos[0].x + 0.5, tpos[0].y + 0.5,
			grad_rgb((double)i / step, color, ncolor));
		tpos[0].x += dpos.x;
		tpos[0].y += dpos.y;
		i += 1;
	}
}
