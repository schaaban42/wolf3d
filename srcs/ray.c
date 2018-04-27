/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 14:27:47 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 17:45:11 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double			*get_closer_h(double x, double y, double a, t_wolf *wolf)
{
	double		*p_a;

	if (a == 0 || a == 180)
		return (NULL);
	if ((!(p_a = (double*)malloc(sizeof(double) * 2))))
		error_handler(W_ERROR_MALLOC, wolf);
	else if (a < 180)
		p_a[1] = floor(y / WALL_SIZE) * WALL_SIZE;
	else
		p_a[1] = floor(y / WALL_SIZE) * WALL_SIZE + WALL_SIZE;
	p_a[0] = x + (y - p_a[1]) / tan(a * M_PI / 180);
	return (p_a);
}

double			*get_closer_v(double x, double y, double a, t_wolf *wolf)
{
	double		*p_a;

	if (a == 90 || a == 270)
		return (NULL);
	if ((!(p_a = (double*)malloc(sizeof(double) * 2))))
		error_handler(W_ERROR_MALLOC, wolf);
	else if (a < 90 || a > 270)
		p_a[0] = floor(x / WALL_SIZE) * WALL_SIZE + WALL_SIZE;
	else
		p_a[0] = floor(x / WALL_SIZE) * WALL_SIZE;
	p_a[1] = y + (x - p_a[0]) * tan(a * M_PI / 180);
	return (p_a);
}

int				ft_raylen(double *r, double *p)
{
	return (sqrt((p[0] - r[0]) * (p[0] - r[0]) +
		(p[1] - r[1]) * (p[1] - r[1])));
}
