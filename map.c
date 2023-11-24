/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:29:19 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/24 14:01:35 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_wordnum(char *s, t_data *data)
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
	if (data->len != 0 && data->len != count)
		error_print(1);
	return (count);
}

void	ft_split_int(int i, char *tmp, t_data *data)
{
	int	j;

	if (tmp == 0)
		return ;
	data->len = check_wordnum(tmp, data);
	data->imap[i] = (int *)malloc(sizeof(int) * data->len);
	data->color[i] = (int *)malloc(sizeof(int) * data->len);
	if (data->imap[i] == 0 || data->color[i] == 0)
		error_print(2);
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

int	check_size(int fd)
{
	char	*tmp;
	int		size;

	size = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == 0 || *tmp == '\n')
		{
			free(tmp);
			break ;
		}
		free(tmp);
		size++;
	}
	return (size);
}

void	make_map(char *file, t_data *data)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(file, O_RDONLY);
	data->size = check_size(fd);
	close(fd);
	if (file_check(file, ".fdf") == 0 || data->size == 0)
		error_print(1);
	data->imap = (int **)malloc(sizeof(int *) * data->size);
	data->color = (int **)malloc(sizeof(int *) * data->size);
	if (data->imap == 0 || data->color == 0)
		error_print(2);
	fd = open(file, O_RDONLY);
	i = 0;
	data->len = 0;
	while (i < data->size)
	{
		tmp = get_next_line(fd);
		ft_split_int(i, tmp, data);
		free(tmp);
		i++;
	}
	if (data->len == 1 && data->size == 1)
		error_print(1);
}
