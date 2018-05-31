/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:14:28 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/18 02:24:01 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		fill_first_tex(int index, SDL_Surface *sf, t_wolf *wolf)
{
	int		i;
	int		j;
	Uint8	*p;

	if (!(wolf->tex[index] =
		(Uint32**)malloc(sizeof(Uint32*) * (WALL_SIZE + 1))))
		error_handler(W_ERROR_MALLOC, wolf);
	i = -1;
	while (++i < WALL_SIZE)
	{
		if (!(wolf->tex[index][i] =
			(Uint32*)malloc(sizeof(Uint32) * (WALL_SIZE))))
			error_handler(W_ERROR_MALLOC, wolf);
		j = -1;
		while (++j < WALL_SIZE)
		{
			p = ((Uint8*)sf->pixels + i *
				sf->pitch + j * sf->format->BytesPerPixel);
			wolf->tex[index][i][j] = (p[0]) | (p[1] << 8) | (p[2] << 16);
		}
	}
	wolf->tex[index][i] = NULL;
}

static void		fill_sky_tex(int index, SDL_Surface *sf, t_wolf *wolf)
{
	int		i;
	int		j;
	Uint8	*p;

	if (!(wolf->tex[index] =
		(Uint32**)malloc(sizeof(Uint32*) * (SKY_H + 1))))
		error_handler(W_ERROR_MALLOC, wolf);
	i = -1;
	while (++i < SKY_H)
	{
		if (!(wolf->tex[index][i] =
			(Uint32*)malloc(sizeof(Uint32) * (SKY_W))))
			error_handler(W_ERROR_MALLOC, wolf);
		j = -1;
		while (++j < SKY_W)
		{
			p = ((Uint8*)sf->pixels + i *
				sf->pitch + j * sf->format->BytesPerPixel);
			wolf->tex[index][i][j] = (p[0]) | (p[1] << 8) | (p[2] << 16);
			//wolf->tex[index][i][j] = ((wolf->tex[index][i][j] & 0xff) << 24) |
			//	((wolf->tex[index][i][j] & 0xffffff00) >> 8);
		}
	}
	wolf->tex[index][i] = NULL;
}

void			ft_fill_tex(int index, SDL_Surface *sf, t_wolf *wolf)
{
	if (index < 10)
		fill_first_tex(index, sf, wolf);
	else
		fill_sky_tex(index, sf, wolf);
}
