/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:52:07 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 15:28:58 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_processing2(int keycode, t_all *all)
{
	if (keycode == 24)
		all->pos->coef += all->pos->dcoef;
	else if (keycode == 27)
	{
		all->pos->coef -= all->pos->dcoef;
		if (all->pos->coef == 0)
		{
			all->pos->coef = all->pos->dcoef;
			return (0);
		}
		else if (all->pos->coef < all->pos->dcoef)
			all->pos->coef = all->pos->dcoef;
	}
	else if (keycode == 123)
		all->pos->ox -= all->pos->dox;
	else if (keycode == 124)
		all->pos->ox += all->pos->dox;
	else if (keycode == 125)
		all->pos->oy += all->pos->doy;
	else if (keycode == 126)
		all->pos->oy -= all->pos->doy;
	return (0);
}

int		key_processing(int keycode, t_all *all)
{
	if (keycode == 53)
	{
		mlx_destroy_window(all->draw->mlx, all->draw->win);
		exit(0);
	}
	if (keycode == 13)
	{
		all->pos->alpha = all->pos->alpha + (M_PI / 180 * 5);
		if (all->pos->alpha > M_PI)
			all->pos->alpha = M_PI - 0.05;
	}
	else if (keycode == 1)
	{
		all->pos->alpha = all->pos->alpha - (M_PI / 180 * 5);
		if (all->pos->alpha < 0)
			all->pos->alpha = 0 + 0.05;
	}
	else if (keycode == 2)
	{
		all->pos->beta = all->pos->beta + (M_PI / 180 * 5);
		if (all->pos->beta > M_PI / 2)
			all->pos->beta = M_PI / 2 - 0.05;
	}
	else if (keycode == 0)
	{
		all->pos->beta = all->pos->beta - (M_PI / 180 * 5);
		if (all->pos->beta < -M_PI / 2)
			all->pos->beta = -M_PI / 2 + 0.05;
	}
	else if (keycode == 14)
		all->pos->gamma = all->pos->gamma + (M_PI / 180 * 5);
	else if (keycode == 12)
		all->pos->gamma = all->pos->gamma - (M_PI / 180 * 5);
	else
		key_processing2(keycode, all);
	mlx_destroy_image(all->draw->mlx, all->draw->img_w);
	do_draw(all);
	return (0);
}
