/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/15 21:27:51 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	int		i;
	Uint32		color;
	double	yreal;
	double max, maxb;
	double nang;
	double dst;
	double	fog;

	i = -1;
	ft_clear_win(wolf);
	while (wolf->rays[++i])
	{
		yreal = ((double)wolf->plan_h * 0.5) - (((double)WALL_SIZE /
			(wolf->rays[i]->dist / wolf->player->dist_pp)) * 0.5);
		switch (wolf->rays[i]->side)
		{
			case O_NORTH:
				color = ft_get_color(255, 0, 0);
				break;
			case O_SOUTH:
				color = ft_get_color(255, 0, 0);
				break;
			case O_EAST:
				color = ft_get_color(0, 0, 255);
				break;
			case O_WEST:
				color = ft_get_color(0, 0, 255);
				break;
			default:
				break;
		}
		max = (double)WALL_SIZE /
			((double)wolf->rays[i]->dist / wolf->player->dist_pp);
		maxb = ((yreal + max) >= wolf->plan_h) ? wolf->plan_h : yreal + max;
		for (int y = 0; y < ceil(yreal); y++)
		{
			int x = (wolf->player->angle * (wolf->plan_w / wolf->fov)) + i;
			if (x >= SKY_W)
				x -= SKY_W;
			color = wolf->tex[10 + wolf->night][y][x];
			ft_put_pixel(i, y, color, wolf);
		}
		for (int y = ceil(maxb); y < wolf->plan_h; y++)
		{
			nang = atan(((double)y - (wolf->plan_h * 0.5)) / wolf->player->dist_pp) * 180.0 / W_PI;
			dst = tan((90.0 - nang) * W_PI / 180.0) * ((double)WALL_SIZE / 2) /
				cos((wolf->player->angle - wolf->rays[i]->angle) * W_PI / 180.0);
			fog = 1 - (dst / (double)(WALL_SIZE * 8));
			fog = (fog < 0) ? 0 : fog;
			fog = (wolf->night) ? fog : 1;
			color = wolf->tex[9]
				[(int)(wolf->player->pos[1] + (sin(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE]
				[(int)(wolf->player->pos[0] + (cos(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE];
			color = color_gradient(0x0A090f, color, fog);
			ft_put_pixel(i, y, color, wolf);
		}
		fog = 1 - (wolf->rays[i]->dist / (double)(WALL_SIZE * 8));
		fog = (fog < 0) ? 0 : fog;
		fog = (wolf->night) ? fog : 1;
		for (int y = (yreal < 0) ? 0 : ceil(yreal); y < maxb; y++)
		{
			color = wolf->tex[wolf->rays[i]->map_v[2] - 1][(int)(
				((((double)y - ceil(yreal)) / max) * (double)WALL_SIZE))][
				abs(wolf->rays[i]->wall_x - ((wolf->rays[i]->side == O_SOUTH ||
					wolf->rays[i]->side == O_EAST) ? (WALL_SIZE - 1) : 0))];
			color = color_gradient(0x0A090f, color, fog);
			ft_put_pixel(i, y, color, wolf);
		}
	}
	draw_minimap(wolf);
}
