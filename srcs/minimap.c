/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:47:50 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/06 22:44:43 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		mm_background(t_wolf *wolf)
{
	int		bg[4];

	bg[0] = MM_POS_X - 3;
	bg[1] = MM_POS_Y - 3;
	bg[2] = MM_SIZE_X + 6;
	bg[3] = MM_SIZE_Y + 6;
	ft_draw_rect(bg, 0x2222ff, wolf);
	bg[0] = MM_POS_X;
	bg[1] = MM_POS_Y;
	bg[2] = MM_SIZE_X;
	bg[3] = MM_SIZE_Y;
	mm_draw_rect(bg, 0, wolf);
}

static void		mm_rays(t_wolf *wolf)
{
	int		i;
	int		v[6];

	i = -1;
	while (wolf->rays[++i])
	{
		v[0] = (((double)(wolf->rays[i]->pos[0] - wolf->player->pos[0]) *
			(double)wolf->mm_wall_size / (double)WALL_SIZE) + (double)MM_O_X);
		v[1] = (((wolf->rays[i]->pos[1] - wolf->player->pos[1]) *
			(double)wolf->mm_wall_size / (double)WALL_SIZE) + (double)MM_O_Y);
		v[2] = MM_O_X;
		v[3] = MM_O_Y;
		v[4] = 0xff0000;
		v[5] = 0xff0000;
		mm_draw_line(v, wolf);
	}
}

static void		mm_map_case(t_wolf *wolf, int r[6],
	double player_mx, double player_my)
{
	r[0] = MM_O_X - ((floor(player_mx) - r[5]) * wolf->mm_wall_size) -
		(player_mx - floor(player_mx)) * wolf->mm_wall_size;
	r[1] = MM_O_Y - ((floor(player_my) - r[4]) * wolf->mm_wall_size) -
		(player_my - floor(player_my)) * wolf->mm_wall_size;
	r[2] = wolf->mm_wall_size;
	r[3] = wolf->mm_wall_size;
	mm_draw_rect(r, 0xffffff, wolf);
}

static void		mm_map(t_wolf *wolf)
{
	double		player_mx;
	double		player_my;
	int			r[6];

	player_mx = (wolf->player->pos[0] / WALL_SIZE);
	player_my = (wolf->player->pos[1] / WALL_SIZE);
	r[4] = (int)player_my - (MM_SIZE_Y / wolf->mm_wall_size / 2) - 2;
	while (++r[4] <= (int)player_my + (MM_SIZE_Y / wolf->mm_wall_size / 2) + 1)
	{
		r[5] = (int)player_mx - (MM_SIZE_X / wolf->mm_wall_size / 2) - 2;
		while (++r[5] <= (int)player_mx +
			(MM_SIZE_X / wolf->mm_wall_size / 2) + 1)
		{
			if (r[4] >= 0 && r[5] >= 0 && r[4] <
				wolf->map_h && r[5] < wolf->map_w)
			{
				if (wolf->map[r[4]][r[5]])
				{
					mm_map_case(wolf, r, player_mx, player_my);
				}
			}
		}
	}
}

void			draw_minimap(t_wolf *wolf)
{
	int		i;
	int		j;

	mm_background(wolf);
	mm_rays(wolf);
	mm_map(wolf);
	i = -4;
	while (++i <= 3)
	{
		j = -4;
		while (++j <= 3)
		{
			minimap_pixel(MM_O_X + i, MM_O_Y + j, 0x00ff00, wolf);
		}
	}
}
