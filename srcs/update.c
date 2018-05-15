/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/12 16:58:38 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_update(t_wolf *wolf)
{
	int			i;

	wolf->player->angle -= (wolf->player->angle >= 360.0) ? 360.0 : 0.0;
	wolf->player->angle += (wolf->player->angle < 0.0) ? 360.0 : 0.0;
	i = -1;
	while (wolf->rays[++i])
	{
		wolf->rays[i]->angle = wolf->player->angle + atan(((i -
			((double)wolf->plan_w / 2)) / wolf->player->dist_pp)) * 180.0 / W_PI;
		wolf->rays[i]->angle -= (wolf->rays[i]->angle >= 360.0) ? 360.0 : 0.0;
		wolf->rays[i]->angle += (wolf->rays[i]->angle < 0.0) ? 360.0 : 0.0;
		ray_cast(wolf->player->pos, wolf->rays[i], wolf);
		wolf->rays[i]->dist = ft_raylen(wolf->rays[i]->pos, wolf->player->pos) *
			cos((wolf->player->angle - wolf->rays[i]->angle) * W_PI / 180.0);
	}
}
