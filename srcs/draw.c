/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:42:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/26 23:54:12 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ray_wall_h(int hit[2], double *a_h, double angle, t_wolf *wolf)
{
	double		xa;
	double		ya;

	ya = (angle < 180) ? -WALL_SIZE : WALL_SIZE;
	xa = -ya / tan(angle * M_PI / 180);
	while (!hit[0])
	{
		if (a_h[0] < 0 || a_h[0] >= (wolf->map_w * WALL_SIZE) ||
			a_h[1] < 0 || a_h[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[0] = 2;
			break;
		}
		if (wolf->map[(int)(a_h[1] / WALL_SIZE)]
			[(int)(a_h[0] / WALL_SIZE)] != 0)
		{
			hit[0] = 1;
			break;
		}
		a_h[0] = a_h[0] + xa;
		a_h[1] = a_h[1] + ya;
	}
}

static void		ray_wall_v(int hit[2], double *a_v, double angle,  t_wolf *wolf)
{
	double		xa;
	double		ya;

	if (angle < 90 || angle > 270)
		xa = WALL_SIZE;
	else
		xa = -WALL_SIZE;
	ya = -xa * tan(angle * M_PI / 180);
	while (!hit[1])
	{
		if (a_v[0] < 0 || a_v[0] >= (wolf->map_w * WALL_SIZE) ||
			a_v[1] < 0 || a_v[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[1] = 2;
			break;
		}
		if (wolf->map[(int)(a_v[1] / WALL_SIZE)]
			[(int)(a_v[0] / WALL_SIZE)] != 0)
		{
			hit[1] = 1;
			break;
		}
		a_v[0] = a_v[0] + xa;
		a_v[1] = a_v[1] + ya;
	}
}

void			ft_draw(t_wolf *wolf)
{
	SDL_SetRenderDrawColor(wolf->render, 0, 0, 0, 255);
	SDL_RenderClear(wolf->render);
	for (int i = 0; i < wolf->map_h; i++)
	{
		for (int j = 0; j < wolf->map_w; j++)
		{
			if (wolf->map[i][j])
			{	
				SDL_Rect re = {j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, WALL_SIZE};
				SDL_SetRenderDrawColor(wolf->render, 255, 255, 255, 255);
				SDL_RenderFillRect(wolf->render, &re);
				SDL_Rect re2 = {j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, WALL_SIZE};
				SDL_SetRenderDrawColor(wolf->render, 255, 0, 255, 255);
				SDL_RenderDrawRect(wolf->render, &re2);
			}
		}
	}
	for (int i = 0; i < wolf->win_w; i++)
	{
		double	angle;

		angle = wolf->player->angle - (wolf->fov / 2) + ((wolf->fov / wolf->win_w) * i);
		if (angle >= 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		double	*a_h = get_closer_h(wolf->player->pos[0], wolf->player->pos[1], angle, wolf);
		double	*a_v = get_closer_v(wolf->player->pos[0], wolf->player->pos[1], angle, wolf);
		int		hit[2];

		hit[0] = 0;
		hit[1] = 0;
		if (a_h)
		{
			ray_wall_h(hit, a_h, angle, wolf);
		}
		if (a_v)
		{
			ray_wall_v(hit, a_v, angle, wolf);
		}
		SDL_SetRenderDrawColor(wolf->render, 255, 0, 0, 255);
		if (hit[0] == 1 && hit[1] == 1)
		{
			if (ft_raylen(a_h, wolf->player->pos) <
				ft_raylen(a_v, wolf->player->pos))
				SDL_RenderDrawLine(wolf->render, wolf->player->pos[0],
					wolf->player->pos[1], a_h[0], a_h[1]);
			else
				SDL_RenderDrawLine(wolf->render, wolf->player->pos[0],
					wolf->player->pos[1], a_v[0], a_v[1]);
		}
		else if (hit[0] == 1)
			SDL_RenderDrawLine(wolf->render, wolf->player->pos[0],
				wolf->player->pos[1], a_h[0], a_h[1]);
		else if (hit[1] == 1)
			SDL_RenderDrawLine(wolf->render, wolf->player->pos[0],
				wolf->player->pos[1], a_v[0], a_v[1]);
		ft_memdel((void**)&a_h);
		ft_memdel((void**)&a_v);
	}
	ft_put_pixel(wolf->player->pos[0], wolf->player->pos[1], 0x00ff00, wolf);
}
