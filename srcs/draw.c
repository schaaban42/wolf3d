/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/11 17:33:59 by schaaban         ###   ########.fr       */
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

	i = -1;
	ft_clear_win(wolf);
	while (wolf->rays[++i])
	{
		yreal = ((double)wolf->win_h * 0.5) - (((double)WALL_SIZE /
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
			(double)(wolf->rays[i]->dist / wolf->player->dist_pp);
		maxb = ((yreal + max) >= wolf->win_h) ? wolf->win_h : yreal + max;
		for (int y = (yreal < 0) ? 0 : ceil(yreal); y < maxb; y++)
		{
			color = wolf->tex[wolf->rays[i]->map_v[2] - 1][(int)(
				((((double)y - yreal) / max) * (double)TEX_SIZE))][
				abs(wolf->rays[i]->wall_x - ((wolf->rays[i]->side == O_SOUTH ||
					wolf->rays[i]->side == O_EAST) ? (TEX_SIZE - 1) : 0))];
			ft_put_pixel(i, y, color, wolf);
		}
		for (int y = ceil(maxb); y <= wolf->win_h; y++)
		{
			nang = atan((y - (wolf->win_h / 2)) / wolf->player->dist_pp) * 180.0 / W_PI;
			dst = tan((90.0 - nang) * W_PI / 180.0) * ((double)WALL_SIZE / 2) /
				cos((wolf->player->angle - wolf->rays[i]->angle) * W_PI / 180.0);
			color = wolf->tex[4]
				[(int)(wolf->player->pos[1] + (sin(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE]
				[(int)(wolf->player->pos[0] + (cos(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE];
			ft_put_pixel(i, y, color, wolf);
			color = wolf->tex[5]
				[(int)(wolf->player->pos[1] + (sin(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE]
				[(TEX_SIZE - 1) - (int)(wolf->player->pos[0] + (cos(wolf->rays[i]->angle * W_PI / 180.0) * dst)) % WALL_SIZE];
			ft_put_pixel(i, (wolf->win_h / 2) - y + (wolf->win_h / 2), color, wolf);
		}
	}
	draw_minimap(wolf);
}
