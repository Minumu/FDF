/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:33:28 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 13:33:55 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_delta(t_position *pos)
{
	int delta;

	if (pos->dy <= pos->dx)
		delta = pos->dx;
	else
		delta = pos->dy;
	pos->delcol[0] = find_abs_double(pos->color1[0] - pos->color0[0]) / delta;
	pos->delcol[1] = find_abs_double(pos->color1[1] - pos->color0[1]) / delta;
	pos->delcol[2] = find_abs_double(pos->color1[2] - pos->color0[2]) / delta;
}

void	my_putpixel(t_draw *draw, t_position *pos, int x, int y)
{
	x = pos->ox + x;
	y = pos->oy + y;
	if (x <= 0 || y <= 0 || x >= draw->w || y >= draw->h)
		return ;
	if (x != pos->x0 && y != pos->y0)
		draw_color(pos);
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8))) =
		(char)(pos->color0[2]);
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 1) =
		(char)(pos->color0[1]);
	*(draw->img + (y * draw->size_l + x * (draw->bpp / 8)) + 2) =
		(char)(pos->color0[0]);
}

void	draw_horizontal_line(t_position *pos, t_draw *draw)
{
	int d;
	int d1;
	int d2;
	int i;

	i = 1;
	d = 2 * pos->dy - pos->dx;
	d1 = 2 * pos->dy;
	d2 = (pos->dy - pos->dx) * 2;
	my_putpixel(draw, pos, pos->x0, pos->y0);
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
		my_putpixel(draw, pos, pos->x, pos->y);
		i++;
		pos->x = pos->x + pos->sx;
	}
}

void	draw_vertical_line(t_position *pos, t_draw *draw)
{
	int d;
	int d1;
	int d2;
	int i;

	i = 1;
	d = 2 * pos->dx - pos->dy;
	d1 = 2 * pos->dx;
	d2 = (pos->dx - pos->dy) * 2;
	my_putpixel(draw, pos, pos->x0, pos->y0);
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
		my_putpixel(draw, pos, pos->x, pos->y);
		i++;
		pos->y = pos->y + pos->sy;
	}
}

void	draw_line(t_position *pos, t_draw *draw)
{
	pos->dx = find_abs(pos->x1 - pos->x0);
	pos->dy = find_abs(pos->y1 - pos->y0);
	pos->sx = pos->x1 >= pos->x0 ? 1 : -1;
	pos->sy = pos->y1 >= pos->y0 ? 1 : -1;
	find_delta(pos);
	if (pos->dy <= pos->dx)
		draw_horizontal_line(pos, draw);
	else
		draw_vertical_line(pos, draw);
}
