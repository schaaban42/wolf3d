/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:57:35 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/05 16:19:44 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_exit(t_wolf *wolf)
{
	int		i;

	i = -1;
	if (wolf->render)
		SDL_FreeSurface(wolf->render);
	if (wolf->win)
		SDL_DestroyWindow(wolf->win);
	if (wolf->rays)
		ft_a2ddel((void***)&wolf->rays);
	if (wolf->map)
		ft_a2ddel((void***)&wolf->map);
	if (wolf->tex)
	{
		while (++i < MAX_TEX)
			ft_a2ddel((void***)&wolf->tex[i]);
		ft_memdel((void**)&wolf->tex);
	}
	SDL_Quit();
	exit(0);
}

static int 	errors_1(int error)
{
	int		a;

	a = 2;
	if (error == W_ERROR_MALLOC)
		ft_putendl_fd("error: m-allocation failed", a++);
	else if (error == W_ERROR_ARGS)
		ft_putendl_fd("usage: wolf3d map_file", a++);
	else if (error == W_ERROR_OPEN)
		ft_putendl_fd("error: could not open file", a++);
	else if (error == W_ERROR_CLOSE)
		ft_putendl_fd("error: could not close file", a++);
	else if (error == W_ERROR_RAY)
		ft_putendl_fd("error: ray out of map", a++);
	else if (error == W_ERROR_TEX)
		ft_putendl_fd("error: textures are not valid", a++);
	else if (error == W_ERROR_TEX_S)
		ft_putendl_fd("error: textures size must be 64x64", a++);
	return ((a != 2) ? 1 : 0);
}

void			error_handler(int error, t_wolf *wolf)
{
	if (error == W_ERROR_SDL_INIT)
	{
		ft_putendl_fd("error: sdl initialization failed", 2);
		exit(0);
	}
	if (!errors_1(error))
	{
		if (error == W_ERROR_READ)
			ft_putendl_fd("error: could not read file", 2);
		else if (error == W_ERROR_FILE)
			ft_putendl_fd("error: file is not valid", 2);
		else if (close(wolf->fd) != 0)
			error_handler(W_ERROR_CLOSE, wolf);
	}
	ft_exit(wolf);
}
