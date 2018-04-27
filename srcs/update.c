/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 17:43:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 18:06:36 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_update(t_wolf *wolf)
{
	if (wolf->player->angle >= 360)
		wolf->player->angle = 0;
	if (wolf->player->angle < 0)
		wolf->player->angle = 359;
}
