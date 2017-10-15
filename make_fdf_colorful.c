/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fdf_colorful.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:53:20 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 17:05:34 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	record_static_color2(char *line, t_map *map, t_position *pos, int i)
{
	int j;
	int c;

	j = 0;
	c = 5;
	while (line[j + 1])
		j++;
	while (line[j] != 'x' && c >= 3)
	{
		map->color = 1;
		pos->coor[i][c] = hex_to_decimal(line, j);
		c--;
		j -= 2;
		if (line[j] == 'x')
		{
			if (c == 4)
			{
				pos->coor[i][c] = 0;
				pos->coor[i][--c] = 0;
			}
			else if (c == 3)
				pos->coor[i][c] = 0;
		}
	}
}

void	record_static_color(char *line, t_map *map, t_position *pos, int i)
{
	init_color(pos, i);
	if (ft_strchr(line, 'x'))
		record_static_color2(line, map, pos, i);
}

int		record_color1(t_position *pos, int i)
{
	if (pos->coor[i][2] < 0 && pos->coor[i][2] >= pos->min_z)
	{
		pos->coor[i][3] = 255 - (255 / find_abs(pos->min_z) *
				find_abs(pos->coor[i][2]));
		pos->coor[i][4] = 255 - (255 / find_abs(pos->min_z) *
				find_abs(pos->coor[i][2]));
		pos->coor[i][5] = 255;
		return (1);
	}
	else if (pos->coor[i][2] == pos->max_z && pos->coor[i][2] > 0)
	{
		pos->coor[i][3] = 255;
		pos->coor[i][4] = 0;
		pos->coor[i][5] = 0;
		return (1);
	}
	else if (pos->coor[i][2] >= pos->max_z / 2 && pos->coor[i][2] < pos->max_z)
	{
		pos->coor[i][3] = 255;
		pos->coor[i][4] = 255 - 255 / (pos->max_z / 2) *
			(pos->coor[i][2] - pos->max_z / 2);
		pos->coor[i][5] = 0;
		return (1);
	}
	return (0);
}

void	record_color2(t_position *pos, int i)
{
	if (pos->coor[i][2] >= pos->max_z / 4 &&
			pos->coor[i][2] <= pos->max_z / 2)
	{
		pos->coor[i][3] = (255 - 45) / (pos->max_z / 4) *
			(pos->coor[i][2] - pos->max_z / 4) + 45;
		pos->coor[i][4] = 166 + (255 - 166) / (pos->max_z / 4) *
			(pos->coor[i][2] - pos->max_z / 4);
		pos->coor[i][5] = 72 - 72 / (pos->max_z / 4) *
			(pos->coor[i][2] - pos->max_z / 4);
	}
	else if (pos->coor[i][2] > 0 && pos->coor[i][2] < pos->max_z / 4)
	{
		pos->coor[i][3] = 255 - (255 - 45) / (pos->max_z / 4) *
			pos->coor[i][2];
		pos->coor[i][4] = 255 - (255 - 166) / (pos->max_z / 4) *
			pos->coor[i][2];
		pos->coor[i][5] = 255 - (255 - 72) / (pos->max_z / 4) *
			pos->coor[i][2];
	}
}

void	record_color(t_map *map, t_position *pos)
{
	int x;
	int y;
	int i;

	i = 0;
	y = -1;
	while (++y < map->map_y)
	{
		x = -1;
		while (++x < map->map_x && map->map[i])
		{
			if (pos->coor[i][2] == 0)
			{
				pos->coor[i][3] = 255;
				pos->coor[i][4] = 255;
				pos->coor[i][5] = 255;
			}
			else if (record_color1(pos, i) == 0)
				record_color2(pos, i);
			i++;
		}
	}
}
