/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:19 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/20 17:21:58 by hyeongsh         ###   ########.fr       */
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

void	ft_split_int(int i, char *tmp, t_data *data)
{
	int	j;

	if (tmp == 0)
		return ;
	data->len = check_wordnum(tmp);
	data->imap[i] = (int *)malloc(sizeof(int) * data->len);
	data->color[i] = (int *)malloc(sizeof(int) * data->len);
	if (data->imap[i] == 0 || data->color[i] == 0)
		exit(1);
	j = 0;
	while (j < data->len)
	{
		data->imap[i][j] = 0;
		while (*tmp == ' ' || *tmp == '\n')
			tmp++;
		while (*tmp != ' ' && *tmp != 0 && *tmp != ',' && *tmp != '\n')
			data->imap[i][j] = data->imap[i][j] * 10 + *tmp++ - '0';
		data->color[i][j] = color_check(&tmp);
		j++;
	}
}

int	file_check(char *file, char *check)
{
	int	i;
	int	j;

	i = 0;
	while (file[i] != 0)
	{
		j = 0;
		while (file[i + j] == check[j])
		{
			j++;
			if (check[j] == 0)
			{
				if (i == 0 || file[i - 1] == '/')
					return (0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	error_print(int flag)
{
	if (flag == 1)
		write(1, "Input error!\n", 13);
	else if (flag == 2)
		write(1, "Malloc error!\n", 14);
	exit(0);
}

void	make_map(char *file, t_data *data)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(file, O_RDONLY);
	data->size = 0;
	while (get_next_line(fd) != 0)
		(data->size)++;
	close(fd);
	if (file_check(file, ".fdf") == 0 || data->size == 0)
		error_print(1);
	data->imap = (int **)malloc(sizeof(int *) * data->size);
	data->color = (int **)malloc(sizeof(int *) * data->size);
	if (data->imap == 0 || data->color == 0)
		error_print(2);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < data->size)
	{
		tmp = get_next_line(fd);
		ft_split_int(i, tmp, data);
		i++;
	}
}
