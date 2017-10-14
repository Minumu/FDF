#include "fdf.h"

int 	check_hex(char *line, int *i)
{
	int col_len;

	col_len = 0;
	if (line[(*i)] == '0' && line[(*i) + 1] == 'x')
		(*i) += 2;
	else
		return (0);
	while (line[(*i)] && line[(*i)] != ' ')
	{
		if (((line[(*i)] >= 'a' && line[(*i)] <= 'f') ||
				(line[(*i)] >= 'A' && line[(*i)] <= 'F') ||
				ft_isdigit(line[(*i)])) && col_len < 6)
		{
			(*i)++;
			col_len++;
		}
		else
			return (0);
	}
	return (1);
}

int 	is_digit(char *line, int *i)
{
	if (line[(*i)] == '-')
	{
		if (line[(*i) + 1] >= 48 && line[(*i) + 1] <= 57)
			(*i)++;
		else
			return (0);
	}
	while (line[(*i)] && line[(*i)] != ',' && line[(*i)] != ' ')
	{
		if (line[(*i)] >= 48 && line[(*i)] <= 57)
			(*i)++;
		else
			return (0);
	}
	return (1);
}

int 	valid_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (is_digit(line, &i) == 0)
			return (0);
		if (line[i] == ',')
		{
			i++;
			if (check_hex(line, &i) == 0)
				return (0);
		}
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (1);
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
