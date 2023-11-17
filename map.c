/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:19 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 20:59:08 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_wordnum(char *s)
{
	int	flag;
	int	count;

	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s != '\n' && *s != ' ' && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (*s == ' ')
			flag = 1;
		s++;
	}
	return (count);
}

void	ft_split_int(int i, char *tmp, t_map *map)
{
	int	j;

	if (tmp == 0)
		return ;
	map->len = check_wordnum(tmp);
	map->imap[i] = (int *)malloc(sizeof(int) * map->len);
	map->color[i] = (int *)malloc(sizeof(int) * map->len);
	if (map->imap[i] == 0 || map->color[i] == 0)
		exit(1);
	j = 0;
	while (j < map->len)
	{
		map->imap[i][j] = 0;
		while (*tmp == ' ' || *tmp == '\n' || *tmp == 0)
			tmp++;
		while (*tmp != ' ' && *tmp != 0 && *tmp != ',' && *tmp != '\n')
			map->imap[i][j] = map->imap[i][j] * 10 + *tmp++ - '0';
		map->color[i][j] = color_check(&tmp);
		j++;
	}
}

void	make_map(char *file, t_map *map)
{
	int		fd;
	char	*tmp;
	int		i;

	fd = open(file, O_RDONLY);
	map->size = 0;
	while (get_next_line(fd) != 0)
		(map->size)++;
	map->imap = (int **)malloc(sizeof(int *) * map->size);
	map->color = (int **)malloc(sizeof(int *) * map->size);
	if (map->imap == 0 || map->color == 0)
		exit(1);
	close(fd);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < map->size)
	{
		tmp = get_next_line(fd);
		ft_split_int(i, tmp, map);
		i++;
	}
}
