/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/03 05:06:38 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->render, 0, 0, 0, 255);
	SDL_RenderClear(wolf->render);
	/*for (int i = 0; i < wolf->map_h; i++)
	{
		for (int j = 0; j < wolf->map_w; j++)
		{
			if (wolf->map[i][j])
			{	
				SDL_Rect re = {j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, WALL_SIZE};
				SDL_SetRenderDrawColor(wolf->render, 255, 255, 255, 255);
				SDL_RenderFillRect(wolf->render, &re);
				SDL_Rect re2 = {j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, WALL_SIZE};
				SDL_SetRenderDrawColor(wolf->render, 255, 0, 255, 255);
				SDL_RenderDrawRect(wolf->render, &re2);
			}
		}
	}*/
	for (int i = 0; i < wolf->win_w; i++)
	{
		double		angle;
		double		*ray;

		angle = wolf->player->angle - (wolf->fov / 2) + ((wolf->fov / (double)wolf->win_w) * (double)i);
		angle = wolf->player->angle + atan(((i - (double)wolf->win_w + ((double)wolf->win_w / 2.0)) / wolf->player->dist_pp)) * 180.0 / M_PI;
		if (angle >= 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		ray = ray_cast(angle, wolf);
		if (ray)
		{
			double	dist;
			double	yreal;

			dist = ft_raylen(ray, wolf->player->pos, angle) * cos((wolf->player->angle - angle) * M_PI / 180.0);
			yreal = (double)(wolf->win_h / 2.0) - (((double)WALL_SIZE / (double)(dist / wolf->player->dist_pp)) / 2);
			SDL_SetRenderDrawColor(wolf->render, 50, 200, 255, 255);
			SDL_RenderDrawLine(wolf->render, i, 0, i, ceil(yreal));
			SDL_SetRenderDrawColor(wolf->render, 255, 190, 55, 255);
			SDL_RenderDrawLine(wolf->render, i, floor(yreal + (double)WALL_SIZE / (double)(dist / wolf->player->dist_pp)), i, wolf->win_h - 1);
			switch (wolf->actual_side)
			{
				case O_NORTH:
					SDL_SetRenderDrawColor(wolf->render, 255, 0, 0, 255);
					break;
				case O_SOUTH:
					SDL_SetRenderDrawColor(wolf->render, 0, 0, 255, 255);
					break;
				case O_EAST:
					SDL_SetRenderDrawColor(wolf->render, 0, 255, 0, 255);
					break;
				case O_WEST:
					SDL_SetRenderDrawColor(wolf->render, 255, 255, 0, 255);
					break;
				default:
					break;
			}
			SDL_RenderDrawLine(wolf->render, i, yreal, i, yreal + (double)WALL_SIZE / (double)(dist / wolf->player->dist_pp));
			ft_memdel((void**)&ray);
		}
	}
}
