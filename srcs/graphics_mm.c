/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_mm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 22:20:11 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/07 22:28:17 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			minimap_pixel(int x, int y, int color, t_wolf *wolf)
{
	if (x >= MM_POS_X && x < MM_POS_X + MM_SIZE &&
		y >= MM_POS_Y && y < MM_POS_Y + MM_SIZE)
		ft_put_pixel(x, y, color, wolf);
}

void			mm_draw_rect(int p[4], int color, t_wolf *wolf)
{
	int		i;
	int		j;

	i = p[1];
	while (i < p[1] + p[3])
	{
		j = p[0];
		while (j < p[0] + p[2])
		{
			minimap_pixel(j, i, color, wolf);
			j++;
		}
		i++;
	}
}
