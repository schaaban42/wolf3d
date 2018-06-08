/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:45:40 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/06 22:09:50 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		inputs_move(t_wolf *wolf)
{
	wolf->player->run = (wolf->keys[SDL_SCANCODE_LSHIFT]) ? 1 : 0;
	wolf->minimap_full = (wolf->keys[SDL_SCANCODE_LCTRL]) ? 1 : 0;
	if (wolf->keys[SDL_SCANCODE_W])
	{
		wolf->player->mv[0] += DELTA * cos(wolf->player->angle);
		wolf->player->mv[1] += DELTA * sin(wolf->player->angle);
	}
	if (wolf->keys[SDL_SCANCODE_S])
	{
		wolf->player->mv[0] -= DELTA * cos(wolf->player->angle);
		wolf->player->mv[1] -= DELTA * sin(wolf->player->angle);
	}
	if (wolf->keys[SDL_SCANCODE_A])
	{
		wolf->player->mv[0] += DELTA * cos((wolf->player->angle - W_R90));
		wolf->player->mv[1] += DELTA * sin((wolf->player->angle - W_R90));
	}
	if (wolf->keys[SDL_SCANCODE_D])
	{
		wolf->player->mv[0] -= DELTA * cos((wolf->player->angle - W_R90));
		wolf->player->mv[1] -= DELTA * sin((wolf->player->angle - W_R90));
	}
}

static void		inputs_extra(t_wolf *wolf)
{
	if (wolf->keys[SDL_SCANCODE_ESCAPE])
		wolf->exit = 1;
	if (wolf->keys[SDL_SCANCODE_Q])
		wolf->player->angle -= (W_R150 * DELTA);
	if (wolf->keys[SDL_SCANCODE_E])
		wolf->player->angle += (W_R150 * DELTA);
}

static void		inputs_events(t_wolf *wolf)
{
	if (wolf->event.type == SDL_MOUSEMOTION)
		wolf->player->angle += wolf->event.motion.xrel * DELTA * MOUSE_SEN;
	if (wolf->event.type == SDL_WINDOWEVENT)
	{
		if (wolf->event.window.event == SDL_WINDOWEVENT_CLOSE)
			wolf->exit = 1;
	}
	if (wolf->event.type == SDL_KEYDOWN)
	{
		if (wolf->event.key.keysym.sym == SDLK_n)
			wolf->night = (wolf->night) ? 0 : 1;
		if (wolf->event.key.keysym.sym == SDLK_b)
			wolf->drunk = (wolf->drunk) ? 0 : 1;
		if (wolf->event.key.keysym.sym == SDLK_m)
			wolf->minimap = (wolf->minimap) ? 0 : 1;
		if (wolf->event.key.keysym.sym == SDLK_1)
			wolf->mm_wall_size *= 0.5;
		if (wolf->event.key.keysym.sym == SDLK_2)
			wolf->mm_wall_size *= 2;
	}
	if (wolf->event.type == SDL_QUIT)
		wolf->exit = 1;
}

void			process_inputs(t_wolf *wolf)
{
	if (DELTA > 1000.0 / wolf->frequency * 2)
		return;
	while (SDL_PollEvent(&wolf->event))
	{
		inputs_events(wolf);
	}
	SDL_PumpEvents();
	wolf->keys = (Uint8*)SDL_GetKeyboardState(NULL);
	inputs_extra(wolf);
	inputs_move(wolf);
}
