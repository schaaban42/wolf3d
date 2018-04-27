/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:23:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 18:56:33 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				main(int argc, char **argv)
{
	t_wolf		wolf;

	wolf.win = NULL;
	wolf.render = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		error_handler(W_ERROR_SDL_INIT, &wolf);
	init_file_read(argc, argv, &wolf);
	init_values(&wolf);
	wolf.win = SDL_CreateWindow("Wolf3D", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		wolf.win_w, wolf.win_h, SDL_WINDOW_SHOWN);
	wolf.render = SDL_CreateRenderer(wolf.win, -1, SDL_RENDERER_ACCELERATED);
	game_loop(&wolf);
	ft_exit(&wolf);
	return (0);
}
