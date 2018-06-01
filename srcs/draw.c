/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 20:16:21 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_sky(int i, t_wolf *wolf)
{
	Uint32	color;
	int		x;
	int		y;
	
	x = (double)((double)((int)(wolf->rays[i]->angle * 10000) %
		abs((int)(W_R60 * 10000))) / (double)(W_R60 * 10000)) * SKY_W;
	y = -1;
	while (++y < wolf->rays[i]->w_start)
	{
		color = wolf->tex[10 + wolf->night][
			(int)((double)y / (double)(wolf->plan_h / 2) * (double)SKY_H)][x];
		ft_put_pixel(i, y, color, wolf);
	}
}

static void		draw_walls(int i, t_wolf *wolf)
{
	int			y;
	Uint32		color;

	wolf->rays[i]->fog = 1 - (wolf->rays[i]->dist / (double)(WALL_SIZE * 8));
	wolf->rays[i]->fog = (wolf->rays[i]->fog < 0) ? 0 : wolf->rays[i]->fog;
	wolf->rays[i]->fog = (wolf->night) ? wolf->rays[i]->fog : 1;
	y = ((wolf->rays[i]->w_start < 0) ? -1 : (ceil(wolf->rays[i]->w_start) - 1));
	while (++y < wolf->rays[i]->w_end)
	{
		color = wolf->tex
			[wolf->rays[i]->map_v[2] - 1]
			[abs((int)((fabs((double)y - wolf->rays[i]->w_start) /
				wolf->rays[i]->w_size) * (double)WALL_SIZE))]
			[abs((int)(wolf->rays[i]->wall_x - ((wolf->rays[i]->side == O_SOUTH
				|| wolf->rays[i]->side == O_EAST) ? (WALL_SIZE - 1) : 0)))];
		if (wolf->night)
			color = color_gradient(0x0A090f, color, wolf->rays[i]->fog);
		ft_put_pixel(i, y, color, wolf);
	}
}

static void		draw_floor(int i, t_wolf *wolf)
{
	double		nang;
	double		dst;
	double		fog;
	Uint32		color;
	int			y;

	y = ceil(wolf->rays[i]->w_end) - 1;
	while (++y < wolf->plan_h)
	{
		nang = atan((y - (wolf->plan_h * 0.5)) / wolf->player->dist_pp);
		dst = tan(W_R90 - nang) * ((double)WALL_SIZE * 0.5) /
			cos(wolf->player->angle - wolf->rays[i]->angle);
		color = wolf->tex[9]
			[abs((int)(wolf->player->pos[1] +
				(sin(wolf->rays[i]->angle) * dst))) % WALL_SIZE]
			[abs((int)(wolf->player->pos[0] +
				(cos(wolf->rays[i]->angle) * dst))) % WALL_SIZE];
		if (wolf->night)
		{
			fog = 1 - (dst / (double)(WALL_SIZE * 8));
			fog = (fog < 0) ? 0 : fog;
			color = color_gradient(0x0A090f, color, fog);
		}
		ft_put_pixel(i, y, color, wolf);
	}
}

void			ft_draw(t_wolf *wolf)
{
	int		i;

	i = -1;
	ft_clear_win(wolf);
	while (wolf->rays[++i])
	{
		draw_sky(i, wolf);
		draw_floor(i, wolf);
		draw_walls(i, wolf);
	}
	(wolf->minimap) ? draw_minimap(wolf) : 0;
}
