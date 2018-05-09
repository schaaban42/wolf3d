/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/08 21:38:04 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_update(t_wolf *wolf)
{
	int			i;

	if (wolf->player->angle >= 360)
		wolf->player->angle -= 360;
	if (wolf->player->angle < 0)
		wolf->player->angle += 360;
	i = -1;
	while (wolf->rays[++i])
	{
		wolf->rays[i]->angle = wolf->player->angle + atan(((i -
			((double)wolf->win_w / 2)) / wolf->player->dist_pp)) * 180.0 / W_PI;
		if (wolf->rays[i]->angle >= 360)
			wolf->rays[i]->angle -= 360;
		if (wolf->rays[i]->angle < 0)
			wolf->rays[i]->angle += 360;
		ray_cast(wolf->player->pos, wolf->rays[i], wolf);
	}
}
