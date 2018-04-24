/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:23:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 17:18:32 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_player	*init_player(t_wolf *wolf)
{
	t_player	*p;

	if (!(p = (t_player*)malloc(sizeof(t_player))))
		error_handler(W_ERROR_MALLOC, wolf);
	p->pos[0] = 96.0;
	p->pos[1] = 96.0;
	p->angle = 30.0;
	p->dist_pp = (wolf->win_w / 2) / tan(p->angle * M_PI / 180);
	return (p);
}

int				main(void)
{
	t_wolf		wolf;
	double		t_curr;
	double		t_last;
	double		t_acc;

	wolf.win = NULL;
	wolf.render = NULL;
	wolf.exit = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		error_handler(W_ERROR_SDL_INIT, &wolf);
	}
	wolf.map_w = 5;
	wolf.map_h = 5;
	wolf.map[0][0] = 1;
	wolf.map[0][1] = 1;
	wolf.map[0][2] = 1;
	wolf.map[0][3] = 1;
	wolf.map[0][3] = 1;
	wolf.map[1][0] = 1;
	wolf.map[1][1] = 0;
	wolf.map[1][2] = 0;
	wolf.map[1][3] = 0;
	wolf.map[1][4] = 1;
	wolf.map[2][0] = 1;
	wolf.map[2][1] = 0;
	wolf.map[2][2] = 0;
	wolf.map[2][3] = 0;
	wolf.map[2][4] = 1;
	wolf.map[3][0] = 1;
	wolf.map[3][1] = 0;
	wolf.map[3][2] = 0;
	wolf.map[3][3] = 1;
	wolf.map[3][4] = 1;
	wolf.map[4][0] = 1;
	wolf.map[4][1] = 1;
	wolf.map[4][2] = 1;
	wolf.map[4][3] = 1;
	wolf.map[4][4] = 1;

	wolf.win_w = 500;
	wolf.win_h = 500;
	wolf.frequency = 144.0;
	wolf.time_step = 1000.0 / (double)wolf.frequency;
	wolf.player = init_player(&wolf);
	wolf.win = SDL_CreateWindow("Wolf3D", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		wolf.win_w, wolf.win_h, SDL_WINDOW_SHOWN);
	wolf.render = SDL_CreateRenderer(wolf.win, -1, SDL_RENDERER_ACCELERATED);
	t_curr = SDL_GetTicks();
	wolf.time_current = t_curr;
	while (wolf.exit != 1)
	{
		t_last = t_curr;
		t_curr = SDL_GetTicks();
		t_acc += (t_curr - t_last);
		while (t_acc >= wolf.time_step)
		{
			wolf.time_last = wolf.time_current;
			wolf.time_current = SDL_GetTicks();
			wolf.delta = (wolf.time_current - wolf.time_last) / 1000;
			process_inputs(&wolf);
			ft_update(&wolf);
			t_acc -= wolf.time_step;
		}
		ft_draw(&wolf);
		SDL_RenderPresent(wolf.render);
	}
	ft_exit(&wolf);
	return (0);
}
