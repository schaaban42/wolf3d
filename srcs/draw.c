/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/03 17:12:59 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *wolf)
{
	ft_clear_win(wolf);
	
	for (int i = 0; i < wolf->win_w; i++)
	{
		double		angle;
		double		*ray;

		angle = wolf->player->angle - (wolf->fov / 2) + ((wolf->fov / (double)wolf->win_w) * (double)i);
		angle = wolf->player->angle + atan(((i - (double)wolf->win_w + ((double)wolf->win_w / 2.0)) / wolf->player->dist_pp)) * 180.0 / M_PI;
		if (angle >= 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		ray = ray_cast(angle, wolf);
		if (ray)
		{
			double	dist;
			double	yreal;
			int		color;

			dist = ft_raylen(ray, wolf->player->pos, angle) * cos((wolf->player->angle - angle) * M_PI / 180.0);
			yreal = (double)(wolf->win_h / 2.0) - (((double)WALL_SIZE / (double)(dist / wolf->player->dist_pp)) / 2);
			/*ft_draw_v_line(i, 0, yreal, 0x22eeff, wolf);
			ft_draw_v_line(i, yreal + (double)WALL_SIZE /
				(double)(dist / wolf->player->dist_pp), wolf->win_h - 1, 0xffaa44, wolf);*/
			double fog = 1 - (dist / 1024);
			fog = (fog < 0) ? 0 : fog;
			switch (wolf->actual_side)
			{
				case O_NORTH:
					color = ft_get_color(255 * fog, 255 * fog, 255 * fog);
					break;
				case O_SOUTH:
					color = ft_get_color(255 * fog, 255 * fog, 255 * fog);
					break;
				case O_EAST:
					color = ft_get_color(220 * fog, 220 * fog, 220 * fog);
					break;
				case O_WEST:
					color = ft_get_color(220 * fog, 220 * fog, 220 * fog);
					break;
				default:
					break;
			}
			ft_draw_v_line(i, yreal, yreal + (double)WALL_SIZE /
				(double)(dist / wolf->player->dist_pp), color, wolf);
			ft_memdel((void**)&ray);
		}
	}
	/*int d = 10;
	for (int i = 0; i < wolf->map_h; i++)
	{
		for (int j = 0; j < wolf->map_w; j++)
		{
			if (wolf->map[i][j])
			{	
				SDL_Rect re = {j * d, i * d, d, d};
				SDL_SetRenderDrawColor(wolf->render, 255, 255, 255, 255);
				SDL_RenderFillRect(wolf->render, &re);
				SDL_Rect re2 = {j * d, i * d, d, d};
				SDL_SetRenderDrawColor(wolf->render, 255, 0, 255, 255);
				SDL_RenderDrawRect(wolf->render, &re2);
			}
		}
	}
	for (int i = -3; i < 3; i++)
	{
		for (int j = -3; j < 3; j++)
		{
			ft_put_pixel(wolf->player->pos[0] / WALL_SIZE * d + i, wolf->player->pos[1] / WALL_SIZE * d + j, 0x00ff00, wolf);
		}
	}*/
}
