/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:23:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 14:53:20 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				main(int argc, char **argv)
{
	t_wolf		wolf;

	wolf.win = NULL;
	wolf.render = NULL;
	wolf.rays = NULL;
	wolf.map = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_handler(W_ERROR_SDL_INIT, &wolf);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	init_file_read(argc, argv, &wolf);
	init_values(&wolf);
	wolf.win = SDL_CreateWindow("Wolf3D", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		wolf.plan_w, wolf.plan_h, SDL_WINDOW_SHOWN);
	wolf.render = SDL_CreateRGBSurface(0, wolf.plan_w, wolf.plan_h, 32,
		0xff0000, 0xff00, 0xff, 0xff000000);
	game_loop(&wolf);
	ft_exit(&wolf);
	return (0);
}
