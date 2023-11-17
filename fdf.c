/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:56:23 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 20:22:37 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_vars	var;
	t_map	map;
	t_data	img;

	if (ac != 2)
		return (0);
	make_map(av[1], &map);
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, 1000, 1000, "FDF");
	img.img = mlx_new_image(var.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	print_map(&img, &map);
	mlx_put_image_to_window(var.mlx, var.win, img.img, 0, 0);
	mlx_loop(var.mlx);
}
