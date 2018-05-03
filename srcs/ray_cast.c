/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:02:10 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/03 04:24:14 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ray_wall_h(int hit[2], double *a_h, double angle, t_wolf *wolf)
{
	double		xa;
	double		ya;

	ya = (angle > 180) ? -WALL_SIZE : WALL_SIZE;
	xa = ya / tan(angle * M_PI / 180);
	while (!hit[0])
	{
		if (a_h[0] < 0 || a_h[0] >= (wolf->map_w * WALL_SIZE) ||
			a_h[1] < 0 || a_h[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[0] = 2;
			break;
		}
		if (wolf->map[(int)(a_h[1] / WALL_SIZE) - (angle > 180 ? 1 : 0)]
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

	xa = (angle < 90 || angle > 270) ? WALL_SIZE : -WALL_SIZE;
	ya = xa * tan(angle * M_PI / 180);
	while (!hit[1])
	{
		if (a_v[0] < 0 || a_v[0] >= (wolf->map_w * WALL_SIZE) ||
			a_v[1] < 0 || a_v[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[1] = 2;
			break;
		}
		if (wolf->map[(int)(a_v[1] / WALL_SIZE)][(int)(a_v[0] / WALL_SIZE) -
			((angle > 90 && angle < 270) ? 1 : 0)] != 0)
		{
			hit[1] = 1;
			break;
		}
		a_v[0] = a_v[0] + xa;
		a_v[1] = a_v[1] + ya;
	}
}

static double	*ray_return(int hit[2], double *a_h, double *a_v, double angle,
	t_wolf *wolf)
{
	if (hit[0] == 1 && hit[1] == 1)
	{
		if (ft_raylen(a_h, wolf->player->pos, angle) < 
			ft_raylen(a_v, wolf->player->pos, angle))
		{
			wolf->actual_side = (angle < 180) ? O_SOUTH : O_NORTH;
			ft_memdel((void**)&a_v);
			return (a_h);
		}
		wolf->actual_side = (angle > 90 && angle < 270) ? O_EAST : O_WEST;
		ft_memdel((void**)&a_h);
		return (a_v);
	}
	if (hit[0] == 1)
	{
		wolf->actual_side = (angle < 180) ? O_SOUTH : O_NORTH;
		ft_memdel((void**)&a_v);
		return (a_h);
	}
	else if (hit[1] == 1)
	{
		wolf->actual_side = (angle > 90 && angle < 270) ? O_EAST : O_WEST;
		ft_memdel((void**)&a_h);
		return (a_v);
	}
	return (NULL);
}

double			*ray_cast(double angle, t_wolf *wolf)
{
	double	*a_h;
	double	*a_v;
	int		hit[2];

	hit[0] = 0;
	hit[1] = 0;
	a_h = get_closer_h(wolf->player->pos[0], wolf->player->pos[1], angle, wolf);
	a_v = get_closer_v(wolf->player->pos[0], wolf->player->pos[1], angle, wolf);
	if (a_h)
		ray_wall_h(hit, a_h, angle, wolf);
	if (a_v)
		ray_wall_v(hit, a_v, angle, wolf);
	return (ray_return(hit, a_h, a_v, angle, wolf));
}
