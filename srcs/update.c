/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/08 01:48:29 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		update_rays(t_wolf *wolf)
{
	int		i;

	i = -1;
	while (wolf->rays[++i])
	{
		wolf->rays[i]->angle = wolf->player->angle + atan(((i -
			((double)wolf->plan_w / 2)) / wolf->player->dist_pp));
		wolf->rays[i]->angle -=
			(wolf->rays[i]->angle >= W_R360) ? W_R360 : W_R0;
		wolf->rays[i]->angle += (wolf->rays[i]->angle < W_R0) ? W_R360 : W_R0;
		ray_cast(wolf->player->pos, wolf->rays[i], wolf);
		wolf->rays[i]->dist = ft_raylen(wolf->rays[i]->pos, wolf->player->pos)
			* cos(wolf->player->angle - wolf->rays[i]->angle);
		wolf->rays[i]->w_size = (double)WALL_SIZE /
			(wolf->rays[i]->dist / wolf->player->dist_pp);
		wolf->rays[i]->w_start = ((double)wolf->plan_h * 0.5) -
			(wolf->rays[i]->w_size * 0.5);
		wolf->rays[i]->w_end = ((wolf->rays[i]->w_start +
			wolf->rays[i]->w_size) > wolf->plan_h) ? wolf->plan_h :
			wolf->rays[i]->w_start + wolf->rays[i]->w_size;
	}
}

static void		update_player(t_wolf *wolf)
{
	wolf->player->angle -= (wolf->player->angle >= W_R360) ? W_R360 : W_R0;
	wolf->player->angle += (wolf->player->angle < W_R0) ? W_R360 : W_R0;
	wolf->player->speed = (!wolf->player->run) ? P_BASE_SPEED : P_SPRINT_SPEED;
	if (wolf->player->run)
		wolf->fov = (wolf->fov + (1 * DELTA) > P_SPRINT_FOV) ?
			P_SPRINT_FOV : wolf->fov + (1 * DELTA);
	else
		wolf->fov = (wolf->fov - (1 * DELTA) < P_BASE_FOV) ?
			P_BASE_FOV : wolf->fov - (1 * DELTA);
	wolf->player->dist_pp = ((double)wolf->plan_w * 0.5) / tan(wolf->fov * 0.5);
	if (wolf->map[(int)(wolf->player->pos[1] / (double)WALL_SIZE)]
		[(int)((wolf->player->pos[0] + (wolf->player->mv[0] *
		wolf->player->speed)) / (double)WALL_SIZE)] == 0)
		wolf->player->pos[0] += (wolf->player->mv[0] * wolf->player->speed);
	if (wolf->map[(int)((wolf->player->pos[1] +
		(wolf->player->mv[1] * wolf->player->speed)) / (double)WALL_SIZE)]
		[(int)(wolf->player->pos[0] / (double)WALL_SIZE)] == 0)
		wolf->player->pos[1] += (wolf->player->mv[1] * wolf->player->speed);
	wolf->player->mv[0] = 0;
	wolf->player->mv[1] = 0;
}

void			ft_update(t_wolf *wolf)
{
	if (wolf->minimap_full)
	{
		wolf->minimap_size[0] = wolf->plan_w - 40;
		wolf->minimap_size[1] = wolf->plan_h - 40;
	}
	else
	{
		wolf->minimap_size[0] = 120;
		wolf->minimap_size[1] = 120;
	}
	wolf->mm_wall_size = (wolf->mm_wall_size > 64) ? 64 : wolf->mm_wall_size;
	wolf->mm_wall_size = (wolf->mm_wall_size < 2) ? 2 : wolf->mm_wall_size;
	update_player(wolf);
	update_rays(wolf);
}
