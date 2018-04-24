/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:24:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/24 16:57:52 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "SDL.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define WALL_SIZE			64

# define DELTA				wolf->delta

# define W_ERROR_SDL_INIT	0
# define W_ERROR_MALLOC		1

typedef struct		s_player
{
	double			pos[2];
	double			angle;
	double			dist_pp;
}					t_player;

typedef struct		s_wolf
{
	SDL_Event		event;
	SDL_Window		*win;
	SDL_Renderer	*render;
	Uint8			*keys;
	int				exit;
	int				win_w;
	int				win_h;
	double			time_last;
	double			time_current;
	double			time_step;
	double			delta;
	double			frequency;
	double			fov;
	double			sub_angle;
	int				map[5][5];
	int				map_w;
	int				map_h;
	t_player		*player;
}					t_wolf;

void			process_inputs(t_wolf *wolf);

void			ft_put_pixel(int x, int y, int color, t_wolf *wolf);
void			ft_draw_v_line(int x, int y1, int y2, int color, t_wolf *wolf);

void			ft_draw(t_wolf *wolf);
void			ft_update(t_wolf *wolf);

void			ft_exit(t_wolf *wolf);
void			error_handler(int error, t_wolf *wolf);

#endif