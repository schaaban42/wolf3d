/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 22:44:33 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	int		i;
	Uint32		color;
	double	yreal;
		double max, maxb;

	i = -1;
	ft_clear_win(wolf);
	while (wolf->rays[++i])
	{
		yreal = (double)(wolf->win_h / 2.0) - (((double)WALL_SIZE /
			(wolf->rays[i]->dist / wolf->player->dist_pp)) * 0.5);
		ft_draw_v_line(i, 0, yreal, 0x99ccff, wolf);
		ft_draw_v_line(i, yreal + (double)WALL_SIZE / (double)
			(wolf->rays[i]->dist / wolf->player->dist_pp),
			wolf->win_h - 1, 0xaaaaaa, wolf);
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
		maxb = (yreal + max >= wolf->win_h) ? wolf->win_h : yreal + max;
		for (int y = (yreal < 0) ? 0 : ceil(yreal); y < maxb; y++)
		{
			color = wolf->tex[wolf->rays[i]->map_v[2] - 1][(int)(
				((((double)y - yreal) / max) * (double)WALL_SIZE))][
				abs(wolf->rays[i]->wall_x - ((wolf->rays[i]->side == O_SOUTH || wolf->rays[i]->side == O_EAST) ? (WALL_SIZE - 1) : 0))];
			ft_put_pixel(i, y, color, wolf);
		}
	}
	draw_minimap(wolf);
}
