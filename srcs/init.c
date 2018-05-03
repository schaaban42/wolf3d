/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:53:07 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/03 16:24:51 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_player	*init_player(t_wolf *wolf)
{
	t_player	*p;

	if (!(p = (t_player*)malloc(sizeof(t_player))))
		error_handler(W_ERROR_MALLOC, wolf);
	p->pos[0] = WALL_SIZE * 1 + WALL_SIZE / 2;
	p->pos[1] = WALL_SIZE * 1 + WALL_SIZE / 2;
	p->angle = 0;
	p->speed = 400;
	p->dist_pp = (double)(wolf->win_w / 2) / tan((wolf->fov / 2) * M_PI / 180);
	return (p);
}

void			game_loop(t_wolf *wolf)
{
	double		t_start;
	double		t_elapsed;
	SDL_Surface	*screen;

	t_start = SDL_GetTicks();
	screen = SDL_GetWindowSurface(wolf->win);
	while (wolf->exit != 1)
	{
		wolf->delta = (SDL_GetTicks() - t_start) / 1000;
		t_start = SDL_GetTicks();
		process_inputs(wolf);
		ft_update(wolf);
		ft_draw(wolf);
		SDL_BlitSurface(wolf->render, NULL, screen, NULL);
		SDL_UpdateWindowSurface(wolf->win);
		t_elapsed = SDL_GetTicks() - t_start;
        if(t_elapsed < wolf->time_step) {
            SDL_Delay(wolf->time_step - t_elapsed);
        }
	}
}

void			init_values(t_wolf *wolf)
{
	wolf->exit = 0;
	wolf->win_w = 320 * 2.5;
	wolf->win_h = 200 * 2.5;
	wolf->fov = 60;
	wolf->frequency = 144.0;
	wolf->time_step = 1000.0 / (double)wolf->frequency;
	wolf->player = init_player(wolf);
}

void			init_file_read(int argc, char **argv, t_wolf *wolf)
{
	if (argc != 2)
		error_handler(W_ERROR_ARGS, wolf);
	if ((wolf->fd = open(argv[1], O_RDONLY)) < 0)
		error_handler(W_ERROR_OPEN, wolf);
	parse_file(wolf);
	if (close(wolf->fd) != 0)
		error_handler(W_ERROR_CLOSE, wolf);
}
