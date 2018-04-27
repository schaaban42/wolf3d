/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:24:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/04/27 02:52:54 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "SDL.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define WALL_SIZE			50

# define DELTA				wolf->delta

# define W_ERROR_SDL_INIT	0
# define W_ERROR_MALLOC		1
# define W_ERROR_FILE		2
# define W_ERROR_READ		6
# define W_ERROR_OPEN		3
# define W_ERROR_CLOSE		4
# define W_ERROR_ARGS		5

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
	int				fd;
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
	int				**map;
	int				map_w;
	int				map_h;
	t_player		*player;
}					t_wolf;

void			process_inputs(t_wolf *wolf);

void			init_file_read(int argc, char **argv, t_wolf *wolf);
void			init_values(t_wolf *wolf);
void			game_loop(t_wolf *wolf);

void			parse_file(t_wolf *wolf);

void			ft_put_pixel(int x, int y, int color, t_wolf *wolf);
void			ft_draw_v_line(int x, int y1, int y2, int color, t_wolf *wolf);

double			*get_closer_h(double x, double y, double a, t_wolf *wolf);
double			*get_closer_v(double x, double y, double a, t_wolf *wolf);
int				ft_raylen(double *r, double *p);

void			ft_draw(t_wolf *wolf);
void			ft_update(t_wolf *wolf);

void			ft_exit(t_wolf *wolf);
void			error_handler(int error, t_wolf *wolf);

#endif
