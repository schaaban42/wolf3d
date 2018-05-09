/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:02:10 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 00:06:42 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ray_wall_h(int hit[2], t_ray *ray, t_wolf *wolf)
{
	double		xa;
	double		ya;

	ya = (ray->angle > 180) ? -WALL_SIZE : WALL_SIZE;
	xa = ya / tan(ray->angle * W_PI / 180.0);
	while (!hit[0])
	{
		if (ray->a_h[0] < 0 || ray->a_h[0] >= (wolf->map_w * WALL_SIZE) ||
			ray->a_h[1] - (ray->angle > 180 ? 1 : 0) < 0 || ray->a_h[1] -
			(ray->angle > 180 ? 1 : 0) >= (wolf->map_h * WALL_SIZE))
		{
			hit[0] = 2;
			break;
		}
		if (wolf->map[(int)(ray->a_h[1] / WALL_SIZE) -
			(ray->angle > 180 ? 1 : 0)][(int)(ray->a_h[0] / WALL_SIZE)] != 0)
		{
			hit[0] = 1;
			break;
		}
		ray->a_h[0] = ray->a_h[0] + xa;
		ray->a_h[1] = ray->a_h[1] + ya;
	}
}

static void		ray_wall_v(int hit[2], t_ray *ray, t_wolf *wolf)
{
	double		xa;
	double		ya;

	xa = (ray->angle < 90 || ray->angle > 270) ? WALL_SIZE : -WALL_SIZE;
	ya = xa * tan(ray->angle * W_PI / 180.0);
	while (!hit[1])
	{
		if (ray->a_v[0] - ((ray->angle > 90 && ray->angle < 270) ? 1 : 0) < 0 ||
			ray->a_v[0] - ((ray->angle > 90 && ray->angle < 270) ? 1 : 0) >=
				(wolf->map_w * WALL_SIZE) ||
			ray->a_v[1] < 0 || ray->a_v[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[1] = 2;
			break;
		}
		if (wolf->map[(int)(ray->a_v[1] / WALL_SIZE)]
			[(int)(ray->a_v[0] / WALL_SIZE) -
			((ray->angle > 90 && ray->angle < 270) ? 1 : 0)] != 0)
		{
			hit[1] = 1;
			break;
		}
		ray->a_v[0] = ray->a_v[0] + xa;
		ray->a_v[1] = ray->a_v[1] + ya;
	}
}

static int		ray_return(int hit[2], t_ray *ray, t_wolf *wolf)
{
	if (hit[0] == 1 && hit[1] == 1)
	{
		if (ft_raylen(ray->a_h, wolf->player->pos) < 
			ft_raylen(ray->a_v, wolf->player->pos))
		{
			ray->side = (ray->angle < 180) ? O_SOUTH : O_NORTH;
			return (W_HORIZONTAL);
		}
		ray->side = (ray->angle > 90 && ray->angle < 270) ? O_EAST : O_WEST;
		return (W_VERTICAL);
	}
	if (hit[0] == 1)
	{
		ray->side = (ray->angle < 180) ? O_SOUTH : O_NORTH;
		return (W_HORIZONTAL);
	}
	else if (hit[1] == 1)
	{
		ray->side = (ray->angle > 90 && ray->angle < 270) ? O_EAST : O_WEST;
		return (W_VERTICAL);
	}
	return (-1);
}

void			ray_cast(double pos[2], t_ray *ray, t_wolf *wolf)
{
	int		hit[2];
	int		r_return;

	hit[0] = 0;
	hit[1] = 0;
	get_closer_h(pos, ray) ? ray_wall_h(hit, ray, wolf) : 0;
	get_closer_v(pos, ray) ? ray_wall_v(hit, ray, wolf) : 0;
	r_return = ray_return(hit, ray, wolf);
	if (r_return == -1)
		error_handler(W_ERROR_RAY, wolf);
	ray->pos[0] = (r_return == W_HORIZONTAL) ? ray->a_h[0] : ray->a_v[0];
	ray->pos[1] = (r_return == W_HORIZONTAL) ? ray->a_h[1] : ray->a_v[1];
}
