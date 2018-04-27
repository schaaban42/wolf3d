/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:45:40 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 18:57:15 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		inputs_move(t_wolf *wolf)
{
	double		mx;
	double		my;

	if (wolf->keys[SDL_SCANCODE_W])
	{
		mx = wolf->player->speed * DELTA * cos(wolf->player->angle * M_PI / 180);
		my = wolf->player->speed * DELTA * sin(wolf->player->angle * M_PI / 180);
		if (wolf->map[(int)(wolf->player->pos[1] / WALL_SIZE)]
			[(int)((wolf->player->pos[0] + mx * 2) / WALL_SIZE)] == 0)
			wolf->player->pos[0] += mx;
		if (wolf->map[(int)((wolf->player->pos[1] - my * 2) / WALL_SIZE)]
			[(int)(wolf->player->pos[0] / WALL_SIZE)] == 0)
			wolf->player->pos[1] -= my;
	}
	if (wolf->keys[SDL_SCANCODE_S])
	{
		mx = wolf->player->speed * DELTA * cos(wolf->player->angle * M_PI / 180);
		my = wolf->player->speed * DELTA * sin(wolf->player->angle * M_PI / 180);
		if (wolf->map[(int)(wolf->player->pos[1] / WALL_SIZE)]
			[(int)((wolf->player->pos[0] - mx * 2) / WALL_SIZE)] == 0)
			wolf->player->pos[0] -= mx;
		if (wolf->map[(int)((wolf->player->pos[1] + my * 2) / WALL_SIZE)]
			[(int)(wolf->player->pos[0] / WALL_SIZE)] == 0)
			wolf->player->pos[1] += my;
	}
	if (wolf->keys[SDL_SCANCODE_A])
	{
		mx = wolf->player->speed * DELTA * cos((wolf->player->angle - 90) * M_PI / 180);
		my = wolf->player->speed * DELTA * sin((wolf->player->angle - 90) * M_PI / 180);
		if (wolf->map[(int)(wolf->player->pos[1] / WALL_SIZE)]
			[(int)((wolf->player->pos[0] + mx * 2) / WALL_SIZE)] == 0)
			wolf->player->pos[0] += mx;
		if (wolf->map[(int)((wolf->player->pos[1] - my * 2) / WALL_SIZE)]
			[(int)(wolf->player->pos[0] / WALL_SIZE)] == 0)
			wolf->player->pos[1] -= my;
	}
	if (wolf->keys[SDL_SCANCODE_D])
	{
		mx = wolf->player->speed * DELTA * cos((wolf->player->angle - 90) * M_PI / 180);
		my = wolf->player->speed * DELTA * sin((wolf->player->angle - 90) * M_PI / 180);
		if (wolf->map[(int)(wolf->player->pos[1] / WALL_SIZE)]
			[(int)((wolf->player->pos[0] - mx * 2) / WALL_SIZE)] == 0)
			wolf->player->pos[0] -= mx;
		if (wolf->map[(int)((wolf->player->pos[1] + my * 2) / WALL_SIZE)]
			[(int)(wolf->player->pos[0] / WALL_SIZE)] == 0)
			wolf->player->pos[1] += my;
	}
}

void			process_inputs(t_wolf *wolf)
{
	if (DELTA > 1000.0 / wolf->frequency * 2)
		return;
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
	if (wolf->keys[SDL_SCANCODE_Q])
		wolf->player->angle -= (110 * DELTA);
	if (wolf->keys[SDL_SCANCODE_E])
		wolf->player->angle += (110 * DELTA);
	inputs_move(wolf);
}
