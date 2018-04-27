/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:45:40 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/26 23:45:03 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		process_inputs(t_wolf *wolf)
{
	while (SDL_PollEvent(&wolf->event))
	{
		if (wolf->event.type == SDL_WINDOWEVENT)
		{
			if (wolf->event.window.event == SDL_WINDOWEVENT_CLOSE)
				wolf->exit = 1;
		}
		if (wolf->event.type == SDL_QUIT)
			wolf->exit = 1;
	}
	SDL_PumpEvents();
	wolf->keys = (Uint8*)SDL_GetKeyboardState(NULL);
	if (wolf->keys[SDL_SCANCODE_ESCAPE])
		wolf->exit = 1;
	if (wolf->keys[SDL_SCANCODE_A])
		wolf->player->angle += (100 * DELTA);
	if (wolf->keys[SDL_SCANCODE_D])
		wolf->player->angle -= (100 * DELTA);
	if (wolf->keys[SDL_SCANCODE_W])
	{
		wolf->player->pos[0] += 150 * DELTA * cos(wolf->player->angle * M_PI / 180);
		wolf->player->pos[1] -= 150 * DELTA * sin(wolf->player->angle * M_PI / 180);
	}
	if (wolf->keys[SDL_SCANCODE_S])
	{
		wolf->player->pos[0] -= 150 * DELTA * cos(wolf->player->angle * M_PI / 180);
		wolf->player->pos[1] += 150 * DELTA * sin(wolf->player->angle * M_PI / 180);
	}
}
