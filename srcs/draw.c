/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 17:10:23 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->render, 0, 0, 0, 255);
	SDL_RenderClear(wolf->render);
	for (int i = 0; i < wolf->map_h; i++)
	{
		for (int j = 0; j < wolf->map_w; j++)
		{
			if (wolf->map[i][j])
			{	
				SDL_Rect re = {j * 64, i * 64, 64, 64};
				SDL_SetRenderDrawColor(wolf->render, 255, 255, 255, 255);
				SDL_RenderFillRect(wolf->render, &re);
				SDL_Rect re2 = {j * 64, i * 64, 64, 64};
				SDL_SetRenderDrawColor(wolf->render, 255, 0, 255, 255);
				SDL_RenderDrawRect(wolf->render, &re2);
			}
		}
	}

	SDL_SetRenderDrawColor(wolf->render, 30, 30, 255, 255);
	SDL_RenderDrawLine(wolf->render, wolf->player->pos[0], wolf->player->pos[1],
		wolf->player->pos[0] + wolf->player->dist_pp * cos(wolf->player->angle * M_PI / 180),
		wolf->player->pos[1] + wolf->player->dist_pp * sin(wolf->player->angle * M_PI / 180));
	ft_put_pixel(wolf->player->pos[0], wolf->player->pos[1], 0x00ff00, wolf);
}
