/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/31 18:49:32 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_update(t_wolf *wolf)
{
	int			i;

	wolf->player->angle -= (wolf->player->angle >= W_R360) ? W_R360 : W_R0;
	wolf->player->angle += (wolf->player->angle < W_R0) ? W_R360 : W_R0;
	i = -1;
	while (wolf->rays[++i])
	{
		wolf->rays[i]->angle = wolf->player->angle + atan(((i -
			((double)wolf->plan_w / 2)) / wolf->player->dist_pp));
		wolf->rays[i]->angle -= (wolf->rays[i]->angle >= W_R360) ? W_R360 : W_R0;
		wolf->rays[i]->angle += (wolf->rays[i]->angle < W_R0) ? W_R360 : W_R0;
		ray_cast(wolf->player->pos, wolf->rays[i], wolf);
		wolf->rays[i]->dist = ft_raylen(wolf->rays[i]->pos, wolf->player->pos) *
			cos(wolf->player->angle - wolf->rays[i]->angle);
		wolf->rays[i]->w_size = (double)WALL_SIZE /
			(wolf->rays[i]->dist / wolf->player->dist_pp);
		wolf->rays[i]->w_start = ((double)wolf->plan_h * 0.5) -
			(wolf->rays[i]->w_size * 0.5);
		wolf->rays[i]->w_end = ((wolf->rays[i]->w_start +
			wolf->rays[i]->w_size) > wolf->plan_h) ? wolf->plan_h :
			wolf->rays[i]->w_start + wolf->rays[i]->w_size;
	}
}
