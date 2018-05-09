/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:47:51 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/07 22:51:40 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_put_pixel(int x, int y, int c, t_wolf *wolf)
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

void			ft_draw_v_line(int x, int y1, int y2, int color, t_wolf *wolf)
{
	if (y1 < 0)
		y1 = 0;
	if (y2 >= wolf->win_h)
		y2 = wolf->win_h - 1;
	while (y1 <= y2)
	{
		ft_put_pixel(x, y1, color, wolf);
		y1++;
	}
}

void			ft_draw_rect(int p[4], int color, t_wolf *wolf)
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

/*void		ft_draw_f_c(int x, int y1, int y2, t_wolf *wolf)
{
	int			i;
	double		fog;

	ft_draw_v_line(x, y1, y2, 0x22ffff, wolf);
	return;
	if (y1 == 0)
	{
		i = -1;
		while (++i < y2)
		{
			fog = 1 - ((double)i / (wolf->win_h / 2));
			fog = (fog < 0) ? 0 : fog;
			ft_put_pixel(x, i,
				ft_get_color(20 * fog, 255 * fog, 255 * fog), wolf);
		}
	}
	else
	{
		i = y1 - 1;
		while (++i < y2)
		{
			fog = ((double)(i - (wolf->win_h / 2)) / (wolf->win_h / 2));
			fog = (fog > 1) ? 1 : fog;
			ft_put_pixel(x, i,
				ft_get_color(255 * fog, 200 * fog, 90 * fog), wolf);
		}
	}
}*/

void			ft_clear_win(t_wolf *wolf)
{
	int			i;
	int			j;
	Uint32		*target;

	i = -1;
	while (++i < wolf->win_h)
	{
		j = -1;
		while (++j < wolf->win_w)
		{
			target = (Uint32*)((Uint8*)wolf->render->pixels + i *
				wolf->render->pitch + j * sizeof(*target));
			*target = (Uint32)0xff000000;
		}
	}
}
