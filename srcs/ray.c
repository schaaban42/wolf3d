/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:27:47 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/10 02:26:55 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_closer_h(double pos[2], t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == 180.0)
		return (0);
	if (ray->angle < 180.0)
	{
		ray->a_h[1] = ceil(pos[1] / (double)WALL_SIZE) * (double)WALL_SIZE;
		ray->a_h[0] = pos[0] + (pos[1] - ray->a_h[1]) /
			-tan(ray->angle * W_PI / 180.0);
	}
	else
	{
		ray->a_h[1] = floor(pos[1] / (double)WALL_SIZE) * (double)WALL_SIZE - 1;
		ray->a_h[0] = pos[0] + (pos[1] - (ray->a_h[1] + 1)) /
			-tan(ray->angle * W_PI / 180.0);
	}
	return (1);
}

int				get_closer_v(double pos[2], t_ray *ray)
{
	if (ray->angle == 90 || ray->angle == 270)
		return (0);
	if (ray->angle < 90 || ray->angle > 270)
	{
		ray->a_v[0] = ceil(pos[0] / (double)WALL_SIZE) * (double)WALL_SIZE;
		ray->a_v[1] = pos[1] + (pos[0] - ray->a_v[0]) *
			-tan(ray->angle * W_PI / 180.0);
	}
	else
	{
		ray->a_v[0] = floor(pos[0] / (double)WALL_SIZE) * (double)WALL_SIZE - 1;
		ray->a_v[1] = pos[1] + (pos[0] - (ray->a_v[0] + 1)) *
			-tan(ray->angle * W_PI / 180.0);
	}
	return (1);
}

double			ft_raylen(double *r, double *p)
{
	return (sqrt((p[0] - r[0]) * (p[0] - r[0]) +
		(p[1] - r[1]) * (p[1] - r[1])));
}


