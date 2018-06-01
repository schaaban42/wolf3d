/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:47:51 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 16:16:11 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_put_pixel(int x, int y, Uint32 c, t_wolf *wolf)
{
	Uint32 *target;
	if (x >= 0 && y >= 0 && x < wolf->plan_w && y < wolf->plan_h &&
		wolf->win && wolf->render)
	{
		target = (Uint32*)(wolf->render->pixels + y *
			wolf->render->pitch + x * wolf->render->format->BytesPerPixel);
		*target = (Uint32)c | (wolf->drunk ? 0x50000000 : 0xff000000);
	}
}

void			ft_draw_v_line(int x, int y1, int y2,
	Uint32 color, t_wolf *wolf)
{
	if (y1 < 0)
		y1 = 0;
	if (y2 >= wolf->plan_h)
		y2 = wolf->plan_h - 1;
	while (y1 <= y2)
	{
		ft_put_pixel(x, y1, color, wolf);
		y1++;
	}
}

void			ft_draw_rect(int p[4], Uint32 color, t_wolf *wolf)
{
	int		i;
	int		j;

	i = p[1];
	while (i < p[1] + p[3])
	{
		j = p[0];
		while (j < p[0] + p[2])
		{
			ft_put_pixel(j, i, color, wolf);
			j++;
		}
		i++;
	}
}

void			ft_clear_win(t_wolf *wolf)
{
	int			i;
	int			j;
	Uint32		*target;

	i = -1;
	while (++i < wolf->plan_h)
	{
		j = -1;
		while (++j < wolf->plan_w)
		{
			target = (Uint32*)(wolf->render->pixels + i *
				wolf->render->pitch + j * sizeof(*target));
			*target = (Uint32)0xff000000;
		}
	}
}
