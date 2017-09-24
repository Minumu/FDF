#include "fdf.h"

t_draw	*create_empty_draw(void)
{
	t_draw *draw;

	draw = malloc(sizeof(t_draw));
	draw->mlx = NULL;
	draw->win = NULL;
	draw->img_w = NULL;
	draw->img = NULL;
	draw->w = 0;
	draw->h = 0;
	return (draw);
}

t_map		*create_empty_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	return (map);
}

t_position		*create_empty_position(void)
{
	t_position *pos;

	pos = malloc(sizeof(t_position));
	pos->coord = 0;
	pos->coef = 1;
	pos->x0 = 0;
	pos->y0 = 0;
	pos->x1 = 0;
	pos->y1 = 0;
	pos->x = 0;
	pos->y = 0;
	pos->dx = 0;
	pos->dy = 0;
	pos->sx = 0;
	pos->sy = 0;
	return (pos);
}

void		free_double_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	else
	{
		while (arr[i])
		{
			ft_strdel(&arr[i]);
			i++;
		}
		free(arr);
	}
}

void	clean_all(t_map *map, t_position *pos)
{
	free_double_arr(map->map);
	free(map);
	free(pos);
}

