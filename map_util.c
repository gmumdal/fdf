/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:58:53 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/11/17 21:01:45 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*choose_check(char *tmp, char *lower, char *upper)
{
	int	i;

	while (*tmp != 0 && *tmp != ' ')
	{
		i = 10;
		while (upper[i] != 0)
		{
			if (upper[i] == *tmp)
				return (upper);
			i++;
		}
		tmp++;
	}
	return (lower);
}

int	hexa_index(char c, char *lower, char *upper)
{
	int	i;

	i = 0;
	while (lower[i] != 0)
	{
		if (c == lower[i])
			return (i + 10);
		i++;
	}
	i = 0;
	while (upper[i] != 0)
	{
		if (c == upper[i])
			return (i + 10);
		i++;
	}
	return (c - '0');
}

int	color_check(char **tmp)
{
	int		color;

	if (**tmp != ',')
		return (0x00FFFFFF);
	color = 0;
	while (**tmp != 'x')
		(*tmp)++;
	(*tmp)++;
	while (**tmp != ' ' && **tmp != 0)
	{
		color = color * 16 + hexa_index(**tmp, "abcdef", "ABCDEF");
		(*tmp)++;
	}
	return (color);
}
