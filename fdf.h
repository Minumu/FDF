/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 13:47:23 by tshevchu          #+#    #+#             */
/*   Updated: 2017/10/15 16:57:49 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/include/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>

# include <stdio.h>

typedef struct	s_draw
{
	void		*mlx;
	void		*win;
	void		*img_w;
	char		*img;
	int			bpp;
	int			size_l;
	int			en;
	int			w;
	int			h;
}				t_draw;

typedef struct	s_map
{
	char		**map;
	int			map_x;
	int			map_y;
	int 		len;
	int			color;
}				t_map;

typedef struct	s_position
{
	int			**coor;
	int			**re_coord;
	int			max_z;
	int			min_z;
	double		coef;
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	double		color0[3];
	double		color1[3];
	double		delcol[3];
	double		alpha;
	double		beta;
	double		gamma;
	int			x;
	int			y;
	int			ox;
	int			oy;
	int			dox;
	int			doy;
	double		dcoef;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
}				t_position;

typedef struct	s_all
{
	t_draw		*draw;
	t_map		*map;
	t_position	*pos;
}				t_all;

t_all			*init_all(void);
int				count_line_length(char *line, t_map *map);
int				valid_line(char *line);
int 			is_error(char *line, t_all *all);
void			record_color(t_map *map, t_position *pos);
void			init_color(t_position *pos, int i);
void			record_static_color(char *line, t_map *map,
t_position *pos, int i);
int				hex_to_decimal(const char *line, int i);
void			centering(t_all *all);
void			calculate_coefficient(t_all *all);
void			do_draw(t_all *all);
void			find_coord(t_position *pos, t_draw *draw, t_map *map);
void			recalculate_coord(t_position *pos, t_map *map);
void			draw_line(t_position *pos, t_draw *draw);
void			draw_color(t_position *pos);
int				key_processing(int keycode, t_all *all);
char			**ft_strjoin_double_arr(char **s1, char **s2);
char			**ft_strdup_double_arr(char **src);
int				find_abs(int nb);
double			find_abs_double(double nb);
void			free_double_arr(char **arr);

#endif
