/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:47:51 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 16:21:01 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_put_pixel(int x, int y, int c, t_wolf *wolf)
{
	if (x >= 0 && y >= 0 && x < wolf->win_w && y < wolf->win_h &&
		wolf->win && wolf->render)
	{
		SDL_SetRenderDrawColor(wolf->render,
			(c & 0xFF0000) >> 16,
			(c & 0x00FF00) >> 8,
			(c & 0x0000FF), 255);
		SDL_RenderDrawPoint(wolf->render, x, y);
		SDL_SetRenderDrawColor(wolf->render, 0, 0, 0, 255);
	}
}

void		ft_draw_v_line(int x, int y1, int y2, int color, t_wolf *wolf)
{
	while (y1 < y2)
	{
		ft_put_pixel(x, y1, color, wolf);
		y1++;
	}
}
