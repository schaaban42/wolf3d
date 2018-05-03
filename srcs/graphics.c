/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:47:51 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/03 17:09:57 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_put_pixel(int x, int y, int c, t_wolf *wolf)
{
	Uint32 *target;
	if (x >= 0 && y >= 0 && x < wolf->win_w && y < wolf->win_h &&
		wolf->win && wolf->render)
	{
		target = (Uint32*)((Uint8*)wolf->render->pixels + y *
			wolf->render->pitch + x * sizeof(*target));
		*target = (Uint32)c | 0xff000000;
	}
}

void		ft_draw_v_line(int x, int y1, int y2, int color, t_wolf *wolf)
{
	while (y1 <= y2)
	{
		ft_put_pixel(x, y1, color, wolf);
		y1++;
	}
}

void		ft_clear_win(t_wolf *wolf)
{
	int			i;
	int			j;

	i = -1;
	while (++i < wolf->win_h)
	{
		j = -1;
		while (++j < wolf->win_w)
		{
			ft_put_pixel(j, i, 0, wolf);
		}
	}
}

int			ft_get_color(int r, int g, int b)
{
	int		color;

	color = (r << 16) | (g << 8) | (b);
	return (color);
}
