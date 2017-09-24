/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:00:40 by tshevchu          #+#    #+#             */
/*   Updated: 2016/12/09 15:53:52 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_toupper(int c)
{
	unsigned char s;

	s = (unsigned char)c;
	if (c < 0 || c > 255)
		return (c);
	if (s >= 97 && s <= 122)
		s = s - 32;
	return (s);
}
