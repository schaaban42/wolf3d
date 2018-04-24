/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 16:13:09 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_update(t_wolf *wolf)
{
	if (wolf->player->angle >= 360)
		wolf->player->angle = 0;
	if (wolf->player->angle < 0)
		wolf->player->angle = 359;
	printf("Angle : %f\n", wolf->player->angle);
}