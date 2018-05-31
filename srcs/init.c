/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:53:07 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 00:45:12 by schaaban         ###   ########.fr       */
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
	p->angle = 0;
	p->speed = 5 * WALL_SIZE;
	p->dist_pp = ((double)wolf->plan_w * 0.5) / tan(wolf->fov * 0.5);
	return (p);
}

static void		init_tex(t_wolf *wolf)
{
	int				i;
	char			*str;

	i = -1;
	if (!(str = ft_strdup("./tex/x.ppm")))
		error_handler(W_ERROR_MALLOC, wolf);
	if (!(wolf->tex = (Uint32***)malloc(sizeof(Uint32**) * (MAX_TEX + 1))))
		error_handler(W_ERROR_MALLOC, wolf);
	while (++i < MAX_TEX)
	{
		str[6] = i + 'a';
		int fd = open(str, O_RDONLY);
		Uint32 **test = ft_read_ppm(fd, wolf);
		wolf->tex[i] = test;
	}
	ft_strdel(&str);
	wolf->tex[i] = NULL;
}

void			game_loop(t_wolf *wolf)
{
	double		t_start;
	double		t_elapsed;
	double		onesec;
	SDL_Surface	*screen;

	t_start = SDL_GetTicks();
	screen = SDL_GetWindowSurface(wolf->win);
	while (wolf->exit != 1)
	{
		wolf->delta = (SDL_GetTicks() - t_start) / 1000;
		onesec += wolf->delta;
		t_start = SDL_GetTicks();
		process_inputs(wolf);
		ft_update(wolf);
		ft_draw(wolf);
		SDL_BlitScaled(wolf->render, NULL, screen, NULL);
		SDL_UpdateWindowSurface(wolf->win);
		t_elapsed = SDL_GetTicks() - t_start;
        if(t_elapsed < wolf->time_step)
            SDL_Delay(wolf->time_step - t_elapsed);
		if (onesec >= 0.35)
			printf("%f\n", 1.0 / wolf->delta + (onesec = 0));
	}
}

void			init_values(t_wolf *wolf)
{
	int		i;

	i = -1;
	wolf->exit = 0;
	wolf->plan_w = 600;
	wolf->plan_h = 400;
	wolf->fov = W_R60;
	wolf->frequency = 1000.0;
	wolf->night = 0;
	wolf->time_step = 1000.0 / (double)wolf->frequency;
	init_tex(wolf);
	wolf->player = init_player(wolf);
	if (!(wolf->rays = (t_ray**)malloc(sizeof(t_ray*) * (wolf->plan_w + 1))))
		error_handler(W_ERROR_MALLOC, wolf);
	while (++i < wolf->plan_w)
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
