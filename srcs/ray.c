/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:27:47 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/16 03:54:56 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				a_is_left(double angle)
{
	if (angle == W_R90 || angle == W_R270)
		return (-1);
	else if (angle > W_R90 && angle < W_R270)
		return (1);
	else
		return (0);
}

int				a_is_up(double angle)
{
	if (angle == W_R180 || angle == W_R0)
		return (-1);
	else if (angle > W_R180)
		return (1);
	else
		return (0);
}

int				get_closer_h(double pos[2], t_ray *ray)
{
	if (tan(ray->angle) == 0)
		return (0);
	if (!a_is_up(ray->angle))
	{
		ray->a_h[1] = ceil(pos[1] / (double)WALL_SIZE) * (double)WALL_SIZE;
		ray->a_h[0] = pos[0] + (pos[1] - ray->a_h[1]) /
			-tan(ray->angle);
	}
	else
	{
		ray->a_h[1] = floor(pos[1] / (double)WALL_SIZE) * (double)WALL_SIZE - 1;
		ray->a_h[0] = pos[0] + (pos[1] - (ray->a_h[1] + 1)) /
			-tan(ray->angle);
	}
	return (1);
}

int				get_closer_v(double pos[2], t_ray *ray)
{
	if (tan(ray->angle) == W_R90 || tan(ray->angle) == W_R270)
		return (0);
	if (!a_is_left(ray->angle))
	{
		ray->a_v[0] = ceil(pos[0] / (double)WALL_SIZE) * (double)WALL_SIZE;
		ray->a_v[1] = pos[1] + (pos[0] - ray->a_v[0]) *
			-tan(ray->angle);
	}
	else
	{
		ray->a_v[0] = floor(pos[0] / (double)WALL_SIZE) * (double)WALL_SIZE - 1;
		ray->a_v[1] = pos[1] + (pos[0] - (ray->a_v[0] + 1)) *
			-tan(ray->angle);
	}
	return (1);
}

double			ft_raylen(double *r, double *p)
{
	return (sqrt((p[0] - r[0]) * (p[0] - r[0]) +
		(p[1] - r[1]) * (p[1] - r[1])));
}


