#include "fdf.h"

void	record_coord(t_map *map, t_position *pos)
{
	int i;
	int x;
	int y;

	i = 0;
	y = 0;
	pos->coord = (int**)malloc(sizeof(int*) * map->map_x * map->map_y);
	while (y < map->map_y)
	{
		x = 0;
		while (x < map->map_x && map->map[i])
		{
			pos->coord[i] = (int*)malloc(sizeof(int) * 3);
			pos->coord[i][0] = x;
			pos->coord[i][1] = y;
			pos->coord[i][2] = ft_atoi(map->map[i]);
			x++;
			i++;
		}
		y++;
	}
}

int 	count_line_length(char *line, t_map *map)
{
	char **split;
	char **temp;
	int len;

	split = ft_strsplit(line, ' ');
	len = 0;
	while (split[len])
		len++;
	if (map->map == NULL)
		map->map = ft_strdup_double_arr(split);
	else
	{
		temp = ft_strdup_double_arr(map->map);
		free_double_arr(map->map);
		map->map = ft_strjoin_double_arr(temp, split);
		free_double_arr(temp);
	}
	map->map_y++;
	free_double_arr(split);
	return (len);
}

void	calculate_coefficient(t_all *all)
{
	if (all->map->map_x > all->map->map_y)
	{
		if (all->draw->h > all->draw->w)
			all->pos->coef = all->draw->w / (all->map->map_x - 1) - all->map->map_y;
		else
		{
			if (all->draw->w / all->map->map_x >
					all->draw->h / all->map->map_y)
				all->pos->coef = all->draw->h / (all->map->map_y - 1) - all->map->map_x;
			else
				all->pos->coef = all->draw->w / (all->map->map_x - 1) - all->map->map_y;
		}
	}
	else
	{
		if (all->draw->h < all->draw->w)
			all->pos->coef = all->draw->h / (all->map->map_y - 1) - all->map->map_x;
		else
		{
			if (all->draw->h / all->map->map_y <
				all->draw->w / all->map->map_x)
				all->pos->coef = all->draw->h / (all->map->map_y - 1) - all->map->map_x;
			else
				all->pos->coef = all->draw->w / (all->map->map_x - 1) - all->map->map_y;
		}
	}
}

void	do_draw(t_all *all)
{
	all->draw = create_empty_draw();
	all->draw->mlx = mlx_init();
	all->draw->w = 600;
	all->draw->h = 600;
	all->draw->win = mlx_new_window(all->draw->mlx,
									all->draw->w + 1, all->draw->h + 1, "fdf");
	all->draw->img_w = mlx_new_image(all->draw->mlx, all->draw->w, all->draw->h);
	all->draw->img = mlx_get_data_addr(all->draw->img_w, &all->draw->bpp,
									   &all->draw->size_l, &all->draw->en);
	printf("SIZE_LINE %d BPP %d\n", all->draw->size_l, all->draw->bpp);
	calculate_coefficient(all);
	find_coord(all->pos, all->draw, all->map);
	mlx_put_image_to_window(all->draw->mlx, all->draw->win,
							all->draw->img_w, 1, 1);
	mlx_loop(all->draw->mlx);
}

int		main(void)
{
	int len;
	int fd;
	char *line;
	t_all *all;

	fd = open("test", O_RDONLY);
	line = NULL;
	all = malloc(sizeof(t_all));
	all->map = create_empty_map();
	all->pos = create_empty_position();
	while (get_next_line(fd, &line))
	{
		len = count_line_length(line, all->map);
		if (all->map->map_x == 0)
			all->map->map_x = len;
		else if (len != all->map->map_x)
		{
			ft_strdel(&line);
			clean_all(all->map, all->pos);
			return (0);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	printf("MAP_X  %d\n", all->map->map_x);
	printf("MAP_Y  %d\n", all->map->map_y);
	record_coord(all->map, all->pos);
	do_draw(all);
	close(fd);
	clean_all(all->map, all->pos);
	return (0);
}