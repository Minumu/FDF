#include "fdf.h"

int 	find_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}

void	recalculate_coord(t_position *pos, t_map *map)
{
	int i;

	i = 0;
	pos->re_coord = (int**)malloc(sizeof(int*) * map->map_x * map->map_y);
	while (i < map->map_x * map->map_y)
	{
		pos->re_coord[i] = malloc(sizeof(int) * 3);
		pos->re_coord[i][0] = (int) ((pos->coord[i][2] * (sin(pos->alpha) * sin(pos->gamma) +
				cos(pos->alpha) * cos(pos->gamma) * sin(pos->beta)) -
				pos->coord[i][1] * (cos(pos->alpha) * sin(pos->gamma) -
						cos(pos->gamma) * sin(pos->alpha) * sin(pos->beta)) +
						pos->coord[i][0] * cos(pos->beta) * cos(pos->gamma)) * pos->coef);
		pos->re_coord[i][1] = (int) ((pos->coord[i][1] * (cos(pos->alpha) * cos(pos->gamma) +
				sin(pos->alpha) * sin(pos->gamma) * sin(pos->beta)) -
				pos->coord[i][2] * (sin(pos->alpha) * cos(pos->gamma) -
						sin(pos->gamma) * cos(pos->alpha) * sin(pos->beta)) +
						pos->coord[i][0] * cos(pos->beta) * sin(pos->gamma)) * pos->coef);
		pos->re_coord[i][2] = (int) ((pos->coord[i][2] * cos(pos->alpha) * cos(pos->beta) -
									  pos->coord[i][0] * sin(pos->beta) +
									  pos->coord[i][1] * cos(pos->beta) * sin(pos->alpha)) * pos->coef);
	i++;
	}
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
			pos->x0 = pos->re_coord[i][0]; // - pos->coord[i][2] * pos->coef * cos(-45));
			pos->x1 = pos->re_coord[i + 1][0]; //- pos->coord[i + 1][2] * pos->coef * cos(-45));
			pos->y0 = pos->re_coord[i][1]; // - pos->coord[i][2] * pos->coef * cos(-45));
			pos->y1 = pos->re_coord[i + 1][1]; //- pos->coord[i + 1][2] * pos->coef * cos(-45));
			j++;
			draw_line(pos, draw, map);
		}
		else if (i < map->map_x * map->map_y)
			j = 0;
		if (i < map->map_x * map->map_y - map->map_x)
		{
			pos->x0 = pos->re_coord[i][0]; // - pos->coord[i][2] * pos->coef * cos(-45));
			pos->x1 = pos->re_coord[i + map->map_x][0]; // - pos->coord[i + map->map_x][2] * pos->coef * cos(-45));
			pos->y0 = pos->re_coord[i][1]; // - pos->coord[i][2] * pos->coef * cos(-45));
			pos->y1 = pos->re_coord[i + map->map_x][1]; // - pos->coord[i + map->map_x][2] * pos->coef * cos(-45));
			draw_line(pos, draw, map);
		}
		i++;
	}
}

void	my_putpixel(t_draw *draw, t_map *map, t_position *pos, int x, int y)
{

	x = draw->w / 2 - ((map->map_x - 1) * pos->coef) / 2 + x - 1;
	y = draw->h / 2 - ((map->map_y - 1) * pos->coef) / 2 + y - 1;
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8))) = (char)255;
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 1) = (char)255;
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 2) = (char)255;
}

void	draw_line(t_position *pos, t_draw *draw, t_map *map)
{
	int d;
	int d1;
	int d2;
	int i;

	i = 1;
	pos->dx = find_abs(pos->x1 - pos->x0);
	pos->dy = find_abs(pos->y1 - pos->y0);
	pos->sx = pos->x1 >= pos->x0 ? 1 : -1;
	pos->sy = pos->y1 >= pos->y0 ? 1 : -1;
	if (pos->dy <= pos->dx)
	{
		d = 2 * pos->dy - pos->dx;
		d1 = 2 * pos->dy;
		d2 = (pos->dy - pos->dx) * 2;
		my_putpixel(draw, map, pos, pos->x0, pos->y0);
		pos->x = pos->x0 + pos->sx;
		pos->y = pos->y0;
		while (i <= pos->dx)
		{
			if (d > 0)
			{
				d = d + d2;
				pos->y = pos->y + pos->sy;
			}
			else
				d = d + d1;
			my_putpixel(draw, map, pos, pos->x, pos->y);
			i++;
			pos->x = pos->x + pos->sx;
		}
	}
	else
	{
		d = 2 * pos->dx - pos->dy;
		d1 = 2 * pos->dx;
		d2 = (pos->dx - pos->dy) * 2;
		my_putpixel(draw, map, pos, pos->x0, pos->y0);
		pos->x = pos->x0;
		pos->y = pos->y0 + pos->sy;
		while (i <= pos->dy)
		{
			if (d > 0)
			{
				d = d + d2;
				pos->x = pos->x + pos->sx;
			}
			else
				d = d + d1;
			my_putpixel(draw, map, pos, pos->x, pos->y);
			i++;
			pos->y = pos->y + pos->sy;
		}
	}
}
