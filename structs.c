/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:11:26 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 15:12:24 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_draw			*init_draw(void)
{
	t_draw *draw;

	draw = malloc(sizeof(t_draw));
	draw->mlx = NULL;
	draw->win = NULL;
	draw->img_w = NULL;
	draw->img = NULL;
	draw->w = 900;
	draw->h = 800;
	return (draw);
}

t_map			*init_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->len = 0;
	map->color = 0;
	return (map);
}

t_position		*init_position1(t_position *pos)
{
	pos->dox = 10 * pos->ox / 100;
	pos->doy = 10 * pos->oy / 100;
	pos->dcoef = 0;
	pos->dx = 0;
	pos->dy = 0;
	pos->sx = 0;
	pos->sy = 0;
	return (pos);
}

t_position		*init_position(t_draw *draw)
{
	t_position *pos;

	pos = malloc(sizeof(t_position));
	pos->coor = 0;
	pos->re_coord = 0;
	pos->max_z = 0;
	pos->min_z = 0;
	pos->coef = 1;
	pos->x0 = 0;
	pos->y0 = 0;
	pos->x1 = 0;
	pos->y1 = 0;
	pos->alpha = M_PI * 0.2325;
	pos->beta = M_PI * 0.09;
	pos->gamma = 0;
	pos->x = 0;
	pos->y = 0;
	pos->ox = draw->w / 2;
	pos->oy = draw->h / 2;
	init_position1(pos);
	return (pos);
}

t_all			*init_all(void)
{
	t_all *all;

	all = malloc(sizeof(t_all));
	all->draw = init_draw();
	all->map = init_map();
	all->pos = init_position(all->draw);
	return (all);
}
