/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:53:07 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 03:05:55 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_player	*init_player(t_wolf *wolf)
{
	t_player	*p;

	if (!(p = (t_player*)malloc(sizeof(t_player))))
		error_handler(W_ERROR_MALLOC, wolf);
	p->pos[0] = 150;
	p->pos[1] = 150;
	p->angle = 0;
	p->dist_pp = (wolf->win_w / 2) / tan(wolf->fov * M_PI / 180);
	return (p);
}

void			game_loop(t_wolf *wolf)
{
	double		t_curr;
	double		t_last;
	double		t_acc;

	t_curr = SDL_GetTicks();
	wolf->time_current = t_curr;
	while (wolf->exit != 1)
	{
		t_last = t_curr;
		t_curr = SDL_GetTicks();
		t_acc += (t_curr - t_last);
		while (t_acc >= wolf->time_step)
		{
			wolf->time_last = wolf->time_current;
			wolf->time_current = SDL_GetTicks();
			wolf->delta = (wolf->time_current - wolf->time_last) / 1000;
			process_inputs(wolf);
			ft_update(wolf);
			t_acc -= wolf->time_step;
		}
		ft_draw(wolf);
		SDL_RenderPresent(wolf->render);
	}
}

void			init_values(t_wolf *wolf)
{
	wolf->exit = 0;
	wolf->win_w = 550;
	wolf->win_h = 550;
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
