/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_line_mm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:48:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/07 22:26:05 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		first_case(int ar_i[9], t_wolf *wolf)
{
	int		i;

	i = 0;
	ar_i[6] = ar_i[2]/2;
	while (i < ar_i[2])
	{
		ar_i[0] += ar_i[4];
		ar_i[6] += ar_i[3];
		if (ar_i[6] > ar_i[2])
		{
			ar_i[6] -= ar_i[2];
			ar_i[1] += ar_i[5];
		}
		minimap_pixel(ar_i[0], ar_i[1], color_gradient(ar_i[7], ar_i[8],
			((double)i / (double)ar_i[2])), wolf);
		i++;
	}
}

static void		second_case(int ar_i[9], t_wolf *wolf)
{
	int		i;

	i = 0;
	ar_i[6] = ar_i[3] / 2;
	while (i < ar_i[3])
	{
		ar_i[1] += ar_i[5];
		ar_i[6] += ar_i[2];
		if (ar_i[6] > ar_i[3])
		{
			ar_i[6] -= ar_i[3];
			ar_i[0] += ar_i[4];
		}
		minimap_pixel(ar_i[0], ar_i[1], color_gradient(ar_i[7], ar_i[8],
			((double)i / (double)ar_i[3])), wolf);
		i++;
	}
}

void			mm_draw_line(int cc[6], t_wolf *wolf)
{
	int ar_i[9];

	ar_i[2] = abs(cc[2] - cc[0]);
	ar_i[3] = abs(cc[3] - cc[1]);
	ar_i[4] = (cc[0] < cc[2]) ? 1 : -1;
	ar_i[5] = (cc[1] < cc[3]) ? 1 : -1;
	ar_i[0] = cc[0];
	ar_i[1] = cc[1];
	ar_i[7] = cc[4];
	ar_i[8] = cc[5];
	(ar_i[2] > ar_i[3]) ? first_case(ar_i, wolf) : second_case(ar_i, wolf);
	minimap_pixel(cc[0], cc[1], cc[4], wolf);
	minimap_pixel(cc[2], cc[3], cc[5], wolf);
}
