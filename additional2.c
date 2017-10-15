/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:51:11 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 16:53:03 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_color(t_position *pos, int i)
{
	pos->coor[i][3] = 255;
	pos->coor[i][4] = 255;
	pos->coor[i][5] = 255;
}

int		hex_to_decimal(const char *line, int i)
{
	int		dec;
	int		j;
	char	*hex;

	hex = "0123456789abcdef";
	j = 0;
	dec = 0;
	while (hex[j])
	{
		if (line[i - 1] == hex[j] || line[i - 1] == ft_toupper(hex[j]))
		{
			dec = (int)(pow(16, 1) * j);
			j = 0;
			while (hex[j])
			{
				if (line[i] == hex[j] || line[i] == ft_toupper(hex[j]))
					return (dec += (int)(pow(16, 0) * j));
				j++;
			}
		}
		j++;
	}
	return (0);
}

void	centering(t_all *all)
{
	int i;

	i = 0;
	while (i < all->map->map_x * all->map->map_y)
	{
		all->pos->coor[i][0] -= all->map->map_x / 2;
		all->pos->coor[i][1] -= all->map->map_y / 2;
		i++;
	}
	calculate_coefficient(all);
}
