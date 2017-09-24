/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_with_double_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 12:52:59 by tshevchu          #+#    #+#             */
/*   Updated: 2017/09/01 12:54:05 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_strlen_double_arr(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strdup_double_arr(char **src)
{
	int		i;
	int		src_len;
	char	**str;

	src_len = ft_strlen_double_arr(src);
	str = (char**)malloc(sizeof(char*) * (src_len + 1));
	i = 0;
	if (str)
	{
		while (i < src_len)
		{
			str[i] = ft_strdup(src[i]);
			i++;
		}
		str[src_len] = NULL;
		return (str);
	}
	return (0);
}

char	**ft_strjoin_double_arr(char **s1, char **s2)
{
	char	**new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char**)malloc(sizeof(char*) * (ft_strlen_double_arr(s1) +
		ft_strlen_double_arr(s2) + 1));
	while (s1[i] != '\0')
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = ft_strdup(s2[j]);
		i++;
		j++;
	}
	new[ft_strlen_double_arr(s1) + ft_strlen_double_arr(s2)] = NULL;
	return (new);
}
