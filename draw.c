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
		pos->re_coord[i][0] = (int) ((pos->coord[i][2]  * (sin(pos->alpha) * sin(pos->gamma) +
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
			pos->x0 = pos->re_coord[i][0];
			pos->x1 = pos->re_coord[i + 1][0];
			pos->y0 = pos->re_coord[i][1];
			pos->y1 = pos->re_coord[i + 1][1];
			pos->z0 = pos->coord[i][2];
			pos->z1 = pos->coord[i + 1][2];
			j++;
			draw_line(pos, draw, i);
		}
		else if (i < map->map_x * map->map_y)
			j = 0;
		if (i < map->map_x * map->map_y - map->map_x)
		{
			pos->x0 = pos->re_coord[i][0];
			pos->x1 = pos->re_coord[i + map->map_x][0];
			pos->y0 = pos->re_coord[i][1];
			pos->y1 = pos->re_coord[i + map->map_x][1];
			pos->z0 = pos->coord[i][2];
			pos->z1 = pos->coord[i + map->map_x][2];
			draw_line(pos, draw, i);
		}
		i++;
	}
}

void	my_putpixel(t_draw *draw, t_position *pos, int x, int y, int i)
{

	x = pos->ox + x;
	y = pos->oy + y;
	if (x <= 0 || y <= 0 || x >= draw->w || y >= draw->h)
		return ;
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8))) = (char)(pos->coord[i][5]);
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 1) = (char)(pos->coord[i][4]);
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 2) = (char)(pos->coord[i][3]);
}

void	draw_line(t_position *pos, t_draw *draw, int k)
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
		my_putpixel(draw, pos, pos->x0, pos->y0, k);
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
			my_putpixel(draw, pos, pos->x, pos->y, k);
			i++;
			pos->x = pos->x + pos->sx;
		}
	}
	else
	{
		d = 2 * pos->dx - pos->dy;
		d1 = 2 * pos->dx;
		d2 = (pos->dx - pos->dy) * 2;
		my_putpixel(draw, pos, pos->x0, pos->y0, k);
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
			my_putpixel(draw, pos, pos->x, pos->y, k);
			i++;
			pos->y = pos->y + pos->sy;
		}
	}
}
