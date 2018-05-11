/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:53:07 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/11 16:52:03 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_player	*init_player(t_wolf *wolf)
{
	t_player	*p;

	if (!(p = (t_player*)malloc(sizeof(t_player))))
		error_handler(W_ERROR_MALLOC, wolf);
	p->pos[0] = (double)WALL_SIZE * 1.0 + (double)WALL_SIZE / 2;
	p->pos[1] = (double)WALL_SIZE * 1.0 + (double)WALL_SIZE / 2;
	p->angle = 45;
	p->speed = 5 * WALL_SIZE;
	p->dist_pp = ((double)wolf->win_w / 2) / tan((wolf->fov * 0.5) * M_PI / 180);
	return (p);
}

static void		init_tex(t_wolf *wolf)
{
	int				i;
	SDL_Surface		*a_tex;
	char			*str;

	i = -1;
	if (!(str = ft_strdup("./tex/1.bmp")))
		error_handler(W_ERROR_MALLOC, wolf);
	while (++i < MAX_TEX)
	{
		str[6] = i + 1 + '0';
		if (!(a_tex = SDL_LoadBMP(str)))
			error_handler(W_ERROR_MALLOC, wolf);
		if (a_tex->w != TEX_SIZE || a_tex->h != TEX_SIZE)
			error_handler(W_ERROR_TEX_S, wolf);
		ft_fill_tex(i, a_tex, wolf);
		SDL_FreeSurface(a_tex);
	}
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
        if(t_elapsed < wolf->time_step)
            SDL_Delay(wolf->time_step - t_elapsed);
	}
}

void			init_values(t_wolf *wolf)
{
	int		i;

	i = -1;
	wolf->exit = 0;
	wolf->win_w = 600;
	wolf->win_h = 400;
	wolf->fov = 60;
	wolf->frequency = 144.0;
	wolf->time_step = 1000.0 / (double)wolf->frequency;
	init_tex(wolf);
	wolf->player = init_player(wolf);
	if (!(wolf->rays = (t_ray**)malloc(sizeof(t_ray*) * (wolf->win_w + 1))))
		error_handler(W_ERROR_MALLOC, wolf);
	while (++i < wolf->win_w)
		if (!(wolf->rays[i] = (t_ray*)malloc(sizeof(t_ray))))
			error_handler(W_ERROR_MALLOC, wolf);
	wolf->rays[i] = NULL;
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
