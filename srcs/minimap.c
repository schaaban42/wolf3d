/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 17:47:50 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 16:07:19 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_minimap(t_wolf *wolf)
{
	int		bg[4];
	int 	wall;

	wall = 20;
	bg[0] = MM_POS_X - 3;
	bg[1] = MM_POS_Y - 3;
	bg[2] = MM_SIZE + 6;
	bg[3] = MM_SIZE + 6;
	ft_draw_rect(bg, 0x2222ff, wolf);
	bg[0] = MM_POS_X;
	bg[1] = MM_POS_Y;
	bg[2] = MM_SIZE;
	bg[3] = MM_SIZE;
	mm_draw_rect(bg, 0, wolf);
	int		i;

	i = -1;
	while (wolf->rays[++i])
	{
		int v[6];
		v[0] = (((double)(wolf->rays[i]->pos[0] - wolf->player->pos[0]) *
			(double)wall / (double)WALL_SIZE) + (double)MM_O_X);
		v[1] = (((wolf->rays[i]->pos[1] - wolf->player->pos[1]) *
			(double)wall / (double)WALL_SIZE) + (double)MM_O_Y);
		v[2] = MM_O_X;
		v[3] = MM_O_Y;
		v[4] = 0xff0000;
		v[5] = 0xff0000;
		mm_draw_line(v, wolf);
	}
	double player_mx, player_my;

	player_mx = (wolf->player->pos[0] / WALL_SIZE);
	player_my = (wolf->player->pos[1] / WALL_SIZE);
	for (int i = (int)player_my - (MM_SIZE / wall / 2) - 1; i <= (int)player_my + (MM_SIZE / wall / 2) + 1; i++)
	{
		for (int j = (int)player_mx - (MM_SIZE / wall / 2) - 1; j <= (int)player_mx + (MM_SIZE / wall / 2) + 1; j++)
		{
			if (i >= 0 && j >= 0 && i < wolf->map_w && j < wolf->map_h)
			{
				if (wolf->map[i][j])
				{
					int r[4];
					r[0] = MM_O_X - ((floor(player_mx) - j) * wall) - (player_mx - floor(player_mx)) * wall;
					r[1] = MM_O_Y - ((floor(player_my) - i) * wall) - (player_my - floor(player_my)) * wall;
					r[2] = wall;
					r[3] = wall;
					mm_draw_rect(r, 0xffffff, wolf);
				}
			}
		}
	}
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -3; j <= 3; j++)
		{
			minimap_pixel(MM_O_X + i, MM_O_Y + j, 0x00ff00, wolf);
		}
	}
}
