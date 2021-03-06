/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:02:10 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 14:55:15 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ray_wall_h(int hit[2], t_ray *ray, t_wolf *wolf)
{
	double		xa;
	double		ya;

	ya = (a_is_up(ray->angle)) ? -WALL_SIZE : WALL_SIZE;
	xa = ya / tan(ray->angle);
	while (!hit[0])
	{
		if (ray->a_h[0] < 0 || ray->a_h[0] >= (wolf->map_w * WALL_SIZE) ||
			ray->a_h[1] < 0 || ray->a_h[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[0] = 2;
			break ;
		}
		if ((ray->map_v[0] = wolf->map[(int)(ray->a_h[1] / WALL_SIZE)]
			[(int)(ray->a_h[0] / WALL_SIZE)]) != 0)
		{
			hit[0] = 1;
			break ;
		}
		ray->a_h[0] = ray->a_h[0] + xa;
		ray->a_h[1] = ray->a_h[1] + ya;
	}
	ray->a_h[1] += ((a_is_up(ray->angle)) ? 1.0 : 0);
}

static void		ray_wall_v(int hit[2], t_ray *ray, t_wolf *wolf)
{
	double		xa;
	double		ya;

	xa = (a_is_left(ray->angle)) ? -WALL_SIZE : WALL_SIZE;
	ya = xa * tan(ray->angle);
	while (!hit[1])
	{
		if (ray->a_v[0] < 0 || ray->a_v[0] >= (wolf->map_w * WALL_SIZE) ||
			ray->a_v[1] < 0 || ray->a_v[1] >= (wolf->map_h * WALL_SIZE))
		{
			hit[1] = 2;
			break ;
		}
		if ((ray->map_v[1] = wolf->map[(int)(ray->a_v[1] / WALL_SIZE)]
			[(int)(ray->a_v[0] / WALL_SIZE)]) != 0)
		{
			hit[1] = 1;
			break ;
		}
		ray->a_v[0] = ray->a_v[0] + xa;
		ray->a_v[1] = ray->a_v[1] + ya;
	}
	ray->a_v[0] += ((a_is_left(ray->angle)) ? 1.0 : 0);
}

static int		ray_return(int hit[2], t_ray *ray, t_wolf *wolf)
{
	if (hit[0] == 1 && hit[1] == 1)
	{
		if (ft_raylen(ray->a_h, wolf->player->pos) <
			ft_raylen(ray->a_v, wolf->player->pos))
		{
			ray->side = (a_is_up(ray->angle)) ? O_NORTH : O_SOUTH;
			return (W_HORIZONTAL);
		}
		ray->side = (a_is_left(ray->angle)) ? O_EAST : O_WEST;
		return (W_VERTICAL);
	}
	if (hit[0] == 1)
	{
		ray->side = (a_is_up(ray->angle)) ? O_NORTH : O_SOUTH;
		return (W_HORIZONTAL);
	}
	else if (hit[1] == 1)
	{
		ray->side = (a_is_left(ray->angle)) ? O_EAST : O_WEST;
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
	if (r_return == W_HORIZONTAL)
	{
		ray->pos[0] = ray->a_h[0];
		ray->pos[1] = ray->a_h[1];
		ray->map_v[2] = ray->map_v[0];
		ray->wall_x = (int)ray->pos[0] % WALL_SIZE;
	}
	else
	{
		ray->pos[0] = ray->a_v[0];
		ray->pos[1] = ray->a_v[1];
		ray->map_v[2] = ray->map_v[1];
		ray->wall_x = (int)ray->pos[1] % WALL_SIZE;
	}
}
