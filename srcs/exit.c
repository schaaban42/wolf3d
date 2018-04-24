/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:57:35 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 16:06:58 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_exit(t_wolf *wolf)
{
	if (wolf->render)
		SDL_DestroyRenderer(wolf->render);
	if (wolf->win)
		SDL_DestroyWindow(wolf->win);
	SDL_Quit();
	exit(0);
}

void	error_handler(int error, t_wolf *wolf)
{
	if (error == W_ERROR_SDL_INIT)
		ft_putendl_fd("error: sdl initialization failed", 2);
	else if (error == W_ERROR_MALLOC)
		ft_putendl_fd("error: m-allocation failed", 2);
	ft_exit(wolf);
}
