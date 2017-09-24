#ifndef FDF_H
# define FDF_H
# include "libft/include/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>

# include <stdio.h> //  DELETE ///

typedef struct	s_draw
{
	void		*mlx;
	void		*win;
	void		*img_w;
	char		*img;
	int 		bpp;
	int 		size_l;
	int 		en;
	int 		w;
	int 		h;
}				t_draw;

typedef struct	s_map
{
	char		**map;
	int 		map_x;
	int 		map_y;
}				t_map;

typedef struct	s_position
{
	int 		**coord;
	int			coef;
	int 		x0;
	int 		x1;
	int			y0;
	int 		y1;
	int 		x;
	int 		y;
	int 		dx;
	int 		dy;
	int			sx;
	int 		sy;
}				t_position;

typedef struct	s_all
{
	t_draw *draw;
	t_map *map;
	t_position *pos;
}				t_all;

t_map		*create_empty_map(void);
t_position		*create_empty_position(void);
t_draw	*create_empty_draw(void);

void	find_coord(t_position *pos, t_draw *draw, t_map *map);
void	draw_line(t_position *pos, t_draw *draw, t_map *map);

char	**ft_strjoin_double_arr(char **s1, char **s2);
char	**ft_strdup_double_arr(char **src);
void	free_double_arr(char **arr);
void	clean_all(t_map *valid, t_position *pos);

#endif