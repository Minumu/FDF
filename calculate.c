/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:34:15 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 13:46:44 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_coefficient(t_all *all)
{
	all->pos->coef = sqrt((double)(all->draw->h * all->draw->w) /
						((double)(all->map->map_x * all->map->map_y * 4)));
	if (all->pos->max_z * all->pos->coef > all->draw->h / 2)
		all->pos->coef = all->draw->h / 2 / all->pos->max_z;
	all->pos->dcoef = 10 * all->pos->coef / 100;
}

void	recalculate_coord(t_position *pos, t_map *map)
{
	int i;

	i = 0;
	while (i < map->map_x * map->map_y)
	{
		pos->re_coord[i][0] = (int)((pos->coor[i][2] * (sin(pos->alpha) *
				sin(pos->gamma) + cos(pos->alpha) * cos(pos->gamma) *
				sin(pos->beta)) - pos->coor[i][1] * (cos(pos->alpha) *
				sin(pos->gamma) - cos(pos->gamma) * sin(pos->alpha) *
				sin(pos->beta)) + pos->coor[i][0] * cos(pos->beta) *
				cos(pos->gamma)) * pos->coef);
		pos->re_coord[i][1] = (int)((pos->coor[i][1] * (cos(pos->alpha) *
				cos(pos->gamma) + sin(pos->alpha) * sin(pos->gamma) *
				sin(pos->beta)) - pos->coor[i][2] * (sin(pos->alpha) *
				cos(pos->gamma) - sin(pos->gamma) * cos(pos->alpha) *
				sin(pos->beta)) + pos->coor[i][0] * cos(pos->beta) *
				sin(pos->gamma)) * pos->coef);
		pos->re_coord[i][2] = (int)((pos->coor[i][2] * cos(pos->alpha) *
				cos(pos->beta) - pos->coor[i][0] * sin(pos->beta) +
				pos->coor[i][1] * cos(pos->beta) * sin(pos->alpha)) *
				pos->coef);
		i++;
	}
}

void	record_all_for_draw(t_position *pos, int i, int j)
{
	pos->x0 = pos->re_coord[i][0];
	pos->x1 = pos->re_coord[j][0];
	pos->y0 = pos->re_coord[i][1];
	pos->y1 = pos->re_coord[j][1];
	pos->color0[0] = pos->coor[i][3];
	pos->color0[1] = pos->coor[i][4];
	pos->color0[2] = pos->coor[i][5];
	pos->color1[0] = pos->coor[j][3];
	pos->color1[1] = pos->coor[j][4];
	pos->color1[2] = pos->coor[j][5];
}

void	find_coord(t_position *pos, t_draw *draw, t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->map_x * map->map_y)
	{
		if (j + 1 < map->map_x)
		{
			record_all_for_draw(pos, i, i + 1);
			draw_line(pos, draw);
			j++;
		}
		else if (i < map->map_x * map->map_y)
			j = 0;
		if (i < map->map_x * map->map_y - map->map_x)
		{
			record_all_for_draw(pos, i, i + map->map_x);
			draw_line(pos, draw);
		}
		i++;
	}
}

void	draw_color(t_position *pos)
{
	if (pos->color0[0] > pos->color1[0])
		pos->color0[0] -= pos->delcol[0];
	else if (pos->color0[0] < pos->color1[0])
		pos->color0[0] += pos->delcol[0];
	if (pos->color0[1] > pos->color1[1])
		pos->color0[1] -= pos->delcol[1];
	else if (pos->color0[1] < pos->color1[1])
		pos->color0[1] += pos->delcol[1];
	if (pos->color0[2] > pos->color1[2])
		pos->color0[2] -= pos->delcol[2];
	else if (pos->color0[2] < pos->color1[2])
		pos->color0[2] += pos->delcol[2];
}
