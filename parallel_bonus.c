/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:17 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/19 21:51:42 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	check_start(t_data *data, t_point *start)
{
	if (data->angle == 0)
	{
		start->x = data->start_x - (data->len / 2 * data->zoom);
		start->y = data->start_y - (data->size / 2 * data->zoom);
	}
	if (data->angle == 1)
	{
		start->x = data->start_x + (data->len / 2 * data->zoom);
		start->y = data->start_y - (data->size / 2 * data->zoom);
	}
	if (data->angle == 2)
	{
		start->x = data->start_x + (data->len / 2 * data->zoom);
		start->y = data->start_y + (data->size / 2 * data->zoom);
	}
	if (data->angle == 3)
	{
		start->x = data->start_x - (data->len / 2 * data->zoom);
		start->y = data->start_y + (data->size / 2 * data->zoom);
	}
}

void	print_line_para(t_data *data, int flag)
{
	t_point	tpos[2];
	t_point	start;
	t_point	angles;
	int		ncolor;

	start.x = data->start_x;
	start.y = data->start_y;
	check_start(data, &start);
	angles.x = M_PI / 2 * data->angle;
	angles.y = M_PI / 2 * data->angle;
	tpos[0].x = start.x + ((data->x * cos(angles.x)
				- data->y * sin(angles.y)) * data->zoom);
	tpos[0].y = start.y + ((data->x * sin(angles.x)
				+ data->y * cos(angles.y)) * data->zoom);
	ncolor = check_flag(tpos, data, flag, angles);
	if (tpos[0].x > 1000 || tpos[0].y > 1000
		|| tpos[1].x > 1000 || tpos[1].y > 1000
		|| tpos[0].x < 0 || tpos[0].y < 0
		|| tpos[1].x < 0 || tpos[1].y < 0)
		return ;
	draw_line(data, tpos, ncolor);
}
