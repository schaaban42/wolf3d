/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:14:28 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 17:11:15 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_fill_tex(int index, SDL_Surface *sf, t_wolf *wolf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < TEX_SIZE)
	{
		j = -1;
		while (++j < TEX_SIZE)
		{
			wolf->tex[index][i][j] = (Uint32)*((Uint32*)(sf->pixels + i *
				sf->pitch + j * sf->format->BytesPerPixel));
			wolf->tex[index][i][j] = ((wolf->tex[index][i][j] & 0xff) << 24) |
				((wolf->tex[index][i][j] & 0xffffff00) >> 8);
		}
	}
}
