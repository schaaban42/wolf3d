/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/08 21:57:49 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	int		i;
	int		color;
	double	dist;
	double	yreal;

	i = 0;
	ft_clear_win(wolf);
	while (wolf->rays[++i])
	{
		dist = ft_raylen(wolf->rays[i]->pos, wolf->player->pos) *
			cos((wolf->player->angle - wolf->rays[i]->angle) * W_PI / 180.0);
		yreal = (double)(wolf->win_h / 2.0) - (((double)WALL_SIZE /
			(dist / wolf->player->dist_pp)) * 0.5);
		ft_draw_v_line(i, 0, yreal, 0x22ffff, wolf);
		ft_draw_v_line(i, yreal + (double)WALL_SIZE / (double)
			(dist / wolf->player->dist_pp), wolf->win_h - 1, 0xffff44, wolf);
		double fog = 1 - (dist / (WALL_SIZE * 8));
		fog = (fog < 0) ? 0 : fog;
		switch (wolf->rays[i]->side)
		{
			case O_NORTH:
				color = ft_get_color(255 * fog, 0 * fog, 0 * fog);
				break;
			case O_SOUTH:
				color = ft_get_color(255 * fog, 0 * fog, 0 * fog);
				break;
			case O_EAST:
				color = ft_get_color(0 * fog, 0 * fog, 255 * fog);
				break;
			case O_WEST:
				color = ft_get_color(0 * fog, 0 * fog, 255 * fog);
				break;
			default:
				break;
		}
		ft_draw_v_line(i, yreal, yreal + (double)WALL_SIZE /
			(double)(dist / wolf->player->dist_pp), color, wolf);
	}
	draw_minimap(wolf);
}
