/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 22:19:17 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/07 22:23:05 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				ft_get_color(int r, int g, int b)
{
	int		color;

	color = (r << 16) | (g << 8) | (b);
	return (color);
}

int				color_gradient(int cs, int ce, double value)
{
	int		c1[3];
	int		c2[3];
	int		cf[3];

	if (value >= 1)
		return (ce);
	if (value <= 0)
		return (cs);
	c1[0] = cs & 0xFF0000;
	c1[1] = cs & 0x00FF00;
	c1[2] = cs & 0x0000FF;
	c2[0] = ce & 0xFF0000;
	c2[1] = ce & 0x00FF00;
	c2[2] = ce & 0x0000FF;
	cf[0] = (c1[0] + (int)((double)(c2[0] - c1[0]) * value)) & 0xFF0000;
	cf[1] = (c1[1] + (int)((double)(c2[1] - c1[1]) * value)) & 0x00FF00;
	cf[2] = (c1[2] + (int)((double)(c2[2] - c1[2]) * value)) & 0x0000FF;
	return (cf[0] | cf[1] | cf[2]);
}
