/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:56:23 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/19 20:57:10 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1000)
	{
		j = 0;
		while (j < 1000)
		{
			my_mlx_pixel_put(data, i, j, 0);
			j++;
		}
		i++;
	}
}

void	check_keycode(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->start_x -= 10;
	if (keycode == RIGHT)
		data->start_x += 10;
	if (keycode == UP)
		data->start_y -= 10;
	if (keycode == DOWN)
		data->start_y += 10;
	if (keycode == BIG)
		data->zoom += 1;
	if (keycode == SMALL && data->zoom > 1)
		data->zoom -= 1;
	if (keycode == TURN_R && data->angle < 3)
		data->angle += 1;
	else if (keycode == TURN_R && data->angle == 3)
		data->angle = 0;
	if (keycode == TURN_L && data->angle != 0)
		data->angle -= 1;
	else if (keycode == TURN_L && data->angle == 0)
		data->angle = 3;
	if (keycode == SIGHT)
		data->sight = 1 - data->sight;
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	check_keycode(keycode, data);
	init_map(data);
	print_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		error_print(1);
	make_map(av[1], &data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1000, 1000, "FDF");
	data.img = mlx_new_image(data.mlx, 1000, 1000);
	data.addr = mlx_get_data_addr(data.img, &data.bpp,
			&data.l_len, &data.endian);
	data.start_x = 500;
	data.start_y = 500;
	data.zoom = 1;
	if (data.size < 20 || data.len < 20)
		data.zoom = 10;
	data.sight = 0;
	data.angle = 0;
	print_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, KEYPRESS, 1L << 0, ft_key_press, &data);
	mlx_loop(data.mlx);
	return (0);
}
