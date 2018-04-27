/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 18:56:44 by schaaban         ###   ########.fr       */
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

		angle = wolf->player->angle - (wolf->fov / 2) + ((wolf->fov / wolf->win_w) * i);
		if (angle >= 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		ray = ray_cast(angle, wolf);
		if (ray)
		{
			double	dist;
			double	yreal;

			dist = ft_raylen(ray, wolf->player->pos) * cos((-(wolf->fov / 2) + ((wolf->fov / (double)wolf->win_w) * i)) * M_PI / 180.0);
			yreal = (wolf->win_h / 2) - ((WALL_SIZE / (dist / wolf->player->dist_pp)) / 2);
			int blur = 128 * (dist / wolf->player->dist_pp);
			if (blur > 255) blur = 255;
			SDL_SetRenderDrawColor(wolf->render, 255 - blur,
				255 - blur, 255 - blur, 255);
			SDL_RenderDrawLine(wolf->render, i, yreal, i, yreal + WALL_SIZE / (dist / wolf->player->dist_pp));
			SDL_SetRenderDrawColor(wolf->render, 50, 200, 255, 255);
			SDL_RenderDrawLine(wolf->render, i, 0, i, yreal);
			SDL_SetRenderDrawColor(wolf->render, 255, 190, 55, 255);
			SDL_RenderDrawLine(wolf->render, i, yreal + WALL_SIZE / (dist / wolf->player->dist_pp), i, wolf->win_h - 1);
			ft_memdel((void**)&ray);
		}
	}
}
