/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:24:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 22:22:06 by schaaban         ###   ########.fr       */
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

# define WALL_SIZE			64
# define TEX_SIZE			64
# define MAX_TEX			9
# define W_PI				(double)3.14159265358979

# define DELTA				wolf->delta

# define W_ERROR_SDL_INIT	0
# define W_ERROR_MALLOC		1
# define W_ERROR_FILE		2
# define W_ERROR_READ		6
# define W_ERROR_OPEN		3
# define W_ERROR_CLOSE		4
# define W_ERROR_ARGS		5
# define W_ERROR_RAY		6
# define W_ERROR_TEX_S		7

# define W_HORIZONTAL		0
# define W_VERTICAL			1

# define O_NORTH			0
# define O_EAST				1
# define O_WEST				2
# define O_SOUTH			3

# define MM_SIZE			100
# define MM_POS_X			wolf->win_w - MM_SIZE - 20
# define MM_POS_Y			20
# define MM_O_X				MM_POS_X + (MM_SIZE / 2)
# define MM_O_Y				MM_POS_Y + (MM_SIZE / 2)

typedef struct		s_player
{
	double			pos[2];
	double			angle;
	double			dist_pp;
	double			speed;
}					t_player;

typedef struct		s_ray
{
	double			pos[2];
	double			a_h[2];
	double			a_v[2];
	double			angle;
	double			dist;
	int				wall_x;
	int				map_v[3];
	int				side;
}					t_ray;

typedef struct		s_wolf
{
	SDL_Event		event;
	SDL_Window		*win;
	SDL_Surface		*render;
	Uint8			*keys;
	int				fd;
	int				exit;
	int				win_w;
	int				win_h;
	double			time_step;
	double			delta;
	double			frequency;
	double			fov;
	double			sub_angle;
	Uint32			tex[MAX_TEX][TEX_SIZE][TEX_SIZE];
	t_ray			**rays;
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

void			ft_put_pixel(int x, int y, Uint32 color, t_wolf *wolf);
void			ft_draw_v_line(int x, int y1, int y2,
	Uint32 color, t_wolf *wolf);
void			ft_draw_rect(int p[4], Uint32 color, t_wolf *wolf);
void			ft_draw_f_c(int x, int y1, int y2, t_wolf *wolf);
void			ft_clear_win(t_wolf *wolf);

void			minimap_pixel(int x, int y, Uint32 color, t_wolf *wolf);
void			mm_draw_rect(int p[4], Uint32 color, t_wolf *wolf);

void			mm_draw_line(int cc[6], t_wolf *wolf);

int				ft_get_color(int r, int g, int b);
int				color_gradient(int cs, int ce, double value);

void			ft_fill_tex(int index, SDL_Surface *sf, t_wolf *wolf);

int				get_closer_h(double pos[2], t_ray *ray);
int				get_closer_v(double pos[2], t_ray *ray);
double			ft_raylen(double *r, double *p);

void			ray_cast(double pos[2], t_ray *ray, t_wolf *wolf);

void			draw_minimap(t_wolf *wolf);

void			ft_draw(t_wolf *wolf);
void			ft_update(t_wolf *wolf);

void			ft_exit(t_wolf *wolf);
void			error_handler(int error, t_wolf *wolf);

#endif
