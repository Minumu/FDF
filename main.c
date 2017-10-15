/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 14:31:34 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 15:24:50 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	record_coord(t_map *map, t_position *pos)
{
	int i;
	int x;
	int y;

	i = 0;
	y = -1;
	pos->coor = (int**)malloc(sizeof(int*) * map->map_x * map->map_y);
	while (++y < map->map_y)
	{
		x = -1;
		while (++x < map->map_x && map->map[i])
		{
			pos->coor[i] = (int*)malloc(sizeof(int) * 6);
			pos->coor[i][0] = x;
			pos->coor[i][1] = y;
			pos->coor[i][2] = ft_atoi(map->map[i]);
			record_static_color(map->map[i], map, pos, i);
			if (pos->coor[i][2] > pos->max_z)
				pos->max_z = pos->coor[i][2];
			if (pos->coor[i][2] < pos->min_z)
				pos->min_z = pos->coor[i][2];
			i++;
		}
	}
}

void	do_draw(t_all *all)
{
	all->draw->img_w = mlx_new_image(all->draw->mlx, all->draw->w,
									all->draw->h);
	all->draw->img = mlx_get_data_addr(all->draw->img_w, &all->draw->bpp,
									&all->draw->size_l, &all->draw->en);
	recalculate_coord(all->pos, all->map);
	find_coord(all->pos, all->draw, all->map);
	mlx_put_image_to_window(all->draw->mlx, all->draw->win,
							all->draw->img_w, 1, 1);
	mlx_hook(all->draw->win, 2, 5, key_processing, all);
	mlx_loop(all->draw->mlx);
}

int		check_map(int fd, t_all *all)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!is_error(line, all))
			return (0);
	}
	if (all->map->len == 0)
	{
		ft_printf("Oh, this map is empty\n");
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

void	init_image(t_all *all, char av[1])
{
	int i;

	i = 0;
	all->draw->mlx = mlx_init();
	all->draw->win = mlx_new_window(all->draw->mlx,
									all->draw->w + 1, all->draw->h + 1, &av[1]);
	record_coord(all->map, all->pos);
	if (all->map->color == 0)
		record_color(all->map, all->pos);
	centering(all);
	all->pos->re_coord = (int**)malloc(sizeof(int*) * all->map->map_x * all->map->map_y);
	while (i < all->map->map_x * all->map->map_y)
	{
		all->pos->re_coord[i] = malloc(sizeof(int) * 3);
		i++;
	}
	do_draw(all);
}

int		main(int ac, char **av)
{
	int		fd;
	t_all	*all;

	if (ac != 2)
	{
		ft_printf("Please, choose one map :)\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("Oh, this map isn't exist :(\n");
		return (0);
	}
	all = init_all();
	if (check_map(fd, all) == 0)
		return (0);
	init_image(all, av[1]);
	return (0);
}
