#include "fdf.h"

void	record_color(t_map *map, t_position *pos)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (y < map->map_y)
	{
		x = 0;
		while (x < map->map_x && map->map[i])
		{
			if (pos->coord[i][2] == 0)
			{
				pos->coord[i][3] = 255;
				pos->coord[i][4] = 255;
				pos->coord[i][5] = 255;
			}
			else if (pos->coord[i][2] < 0)
			{
				pos->coord[i][3] = 255 - ((-pos->coord[i][2] - 1) * 130 / pos->max_z);
				pos->coord[i][4] = 255 - ((-pos->coord[i][2] - 1) * 255 / pos->max_z);
				pos->coord[i][5] = 0;
				if (pos->coord[i][4] < 0)
					pos->coord[i][4] = 0;
			}
			else if (pos->coord[i][2] > 0)
			{
				pos->coord[i][3] = 0;
				pos->coord[i][4] = 0;
				pos->coord[i][5] = 130 + ((pos->coord[i][2] - 1) * 130 / pos->max_z);
				if (pos->coord[i][4] > 255)
					pos->coord[i][4] = 255;
			}
			x++;
			i++;
		}
		y++;
	}
}

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
			pos->coord[i] = (int*)malloc(sizeof(int) * 6);
			pos->coord[i][0] = x;
			pos->coord[i][1] = y;
			pos->coord[i][2] = ft_atoi(map->map[i]);
			if (find_abs(pos->coord[i][2]) > pos->max_z)
				pos->max_z = find_abs(pos->coord[i][2]);
			x++;
			i++;
		}
		y++;
	}
	record_color(map, pos);
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
	all->pos->coef = (sqrt(all->draw->h * all->draw->w /
								 (all->map->map_x * all->map->map_y * 4)));
	if (all->pos->max_z * all->pos->coef > all->draw->h / 2)
		all->pos->coef = all->draw->h / 2 / all->pos->max_z;
	all->pos->dcoef = 10 * all->pos->coef / 100;
}

int 	key_processing(int keycode, t_all *all)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->alpha = all->pos->alpha + (M_PI / 180 * 5);
		printf("A %f \n", all->pos->alpha);
		do_draw(all);
	}
	if (keycode == 124)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->alpha = all->pos->alpha - (M_PI / 180 * 5);
		printf("A %f \n", all->pos->alpha);
		do_draw(all);
	}
	if (keycode == 126)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->beta = all->pos->beta + (M_PI / 180 * 5);
		printf("B %f \n", all->pos->beta);
		do_draw(all);
	}
	if (keycode == 125)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->beta = all->pos->beta - (M_PI / 180 * 5);
		printf("B %f \n", all->pos->beta);
		do_draw(all);
	}
	if (keycode == 0)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->gamma = all->pos->gamma + (M_PI / 180 * 5);
		printf("G %f \n", all->pos->gamma);
		do_draw(all);
	}
	if (keycode == 2)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->gamma = all->pos->gamma - (M_PI / 180 * 5);
		printf("G %f \n", all->pos->gamma);
		do_draw(all);
	}
	if (keycode == 13)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->coef += all->pos->dcoef;
		do_draw(all);
	}
	if (keycode == 1)
	{
		all->pos->coef -= all->pos->dcoef;
		if (all->pos->coef == 0)
		{
			all->pos->coef = all->pos->dcoef;
			return (0);
		}
		else if (all->pos->coef < all->pos->dcoef)
			all->pos->coef = all->pos->dcoef;
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		do_draw(all);
	}
	if (keycode == 5)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->ox -= all->pos->dox;
		do_draw(all);
	}
	if (keycode == 4)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->ox += all->pos->dox;
		do_draw(all);
	}
	if (keycode == 12)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->oy += all->pos->doy;
		do_draw(all);
	}
	if (keycode == 14)
	{
		mlx_destroy_image(all->draw->mlx, all->draw->img_w);
		all->pos->oy -= all->pos->doy;
		do_draw(all);
	}
	return (0);
}

void	centering(t_all *all)
{
	int i;

	i = 0;
	while (i < all->map->map_x * all->map->map_y)
	{
		all->pos->coord[i][0] -= all->map->map_x / 2;
		all->pos->coord[i][1] -= all->map->map_y / 2;
		i++;
	}
}

void	do_draw(t_all *all)
{
	all->draw->img_w = mlx_new_image(all->draw->mlx, all->draw->w, all->draw->h);
	all->draw->img = mlx_get_data_addr(all->draw->img_w, &all->draw->bpp,
									   &all->draw->size_l, &all->draw->en);
	printf("SIZE_LINE %d BPP %d\n", all->draw->size_l, all->draw->bpp);
	recalculate_coord(all->pos, all->map);
	find_coord(all->pos, all->draw, all->map);
	mlx_put_image_to_window(all->draw->mlx, all->draw->win,
							all->draw->img_w, 1, 1);
	mlx_hook(all->draw->win, 2, 5, key_processing, all);
	mlx_loop(all->draw->mlx);
}

int		main(void)
{
	int len;
	int fd;
	char *line;
	t_all *all;

	fd = open("maps/mars.fdf", O_RDONLY);
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
	all->draw = create_empty_draw();
	all->draw->mlx = mlx_init();
	all->draw->w = 800;
	all->draw->h = 900;
	all->pos->ox = all->draw->w / 2;
	all->pos->oy = all->draw->h / 2;
	all->pos->dox = 10 * all->pos->ox / 100;
	all->pos->doy = 10 * all->pos->oy / 100;
	all->draw->win = mlx_new_window(all->draw->mlx,
									all->draw->w + 1, all->draw->h + 1, "fdf");
	centering(all);
	calculate_coefficient(all);
	do_draw(all);
	close(fd);
	clean_all(all->map, all->pos);
	return (0);
}