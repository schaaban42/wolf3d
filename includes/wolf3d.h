/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:24:15 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/08 01:50:54 by schaaban         ###   ########.fr       */
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

# define WALL_SIZE			16
# define MAX_TEX			12
# define W_PI				(double)3.14159265358979
# define W_R0				0.0
# define W_R60				W_PI / 3
# define W_R90				W_PI * 0.5
# define W_R150				(5.0 * W_PI) / 6
# define W_R180				W_PI
# define W_R270				(3 * W_PI) * 0.5
# define W_R360				W_PI * 2.0

# define DELTA				wolf->delta
# define MOUSE_SEN			0.04

# define W_ERROR_SDL_INIT	0
# define W_ERROR_MALLOC		1
# define W_ERROR_FILE		2
# define W_ERROR_READ		6
# define W_ERROR_OPEN		3
# define W_ERROR_CLOSE		4
# define W_ERROR_ARGS		5
# define W_ERROR_RAY		6
# define W_ERROR_TEX_S		7
# define W_ERROR_TEX		8

# define W_HORIZONTAL		0
# define W_VERTICAL			1

# define O_NORTH			0
# define O_EAST				1
# define O_WEST				2
# define O_SOUTH			3

# define MM_SIZE_X			wolf->minimap_size[0]
# define MM_SIZE_Y			wolf->minimap_size[1]
# define MM_POS_X			wolf->plan_w - MM_SIZE_X - 20
# define MM_POS_Y			20
# define MM_O_X				MM_POS_X + (MM_SIZE_X / 2)
# define MM_O_Y				MM_POS_Y + (MM_SIZE_Y / 2)

# define SKY_W				600
# define SKY_H				200

# define P_BASE_SPEED		4 * WALL_SIZE
# define P_SPRINT_SPEED		7 * WALL_SIZE
# define P_BASE_FOV			W_R60
# define P_SPRINT_FOV		P_BASE_FOV * 1.05

typedef struct		s_player
{
	double			pos[2];
	double			mv[2];
	double			angle;
	double			dist_pp;
	double			speed;
	int				run;
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
	double			w_start;
	double			w_size;
	double			w_end;
	double			fog;
}					t_ray;

typedef struct		s_wolf
{
	SDL_Event		event;
	SDL_Window		*win;
	SDL_Surface		*render;
	Uint8			*keys;
	int				fd;
	int				exit;
	int				plan_w;
	int				plan_h;
	double			time_step;
	double			delta;
	double			frequency;
	double			fov;
	Uint32			***tex;
	t_ray			**rays;
	int				**map;
	int				map_w;
	int				map_h;
	int				night;
	int				drunk;
	int				minimap;
	int				minimap_full;
	int				minimap_size[2];
	int				mm_wall_size;
	t_player		*player;
}					t_wolf;

void				process_inputs(t_wolf *wolf);

void				init_file_read(int argc, char **argv, t_wolf *wolf);
void				init_values(t_wolf *wolf);
void				game_loop(t_wolf *wolf);

void				parse_file(t_wolf *wolf);

void				ft_put_pixel(int x, int y, Uint32 color, t_wolf *wolf);
void				ft_draw_v_line(int x, int y1, int y2,
	Uint32 color, t_wolf *wolf);
void				ft_draw_rect(int p[4], Uint32 color, t_wolf *wolf);
void				ft_draw_f_c(int x, int y1, int y2, t_wolf *wolf);
void				ft_clear_win(t_wolf *wolf);

void				minimap_pixel(int x, int y, Uint32 color, t_wolf *wolf);
void				mm_draw_rect(int p[4], Uint32 color, t_wolf *wolf);

void				mm_draw_line(int cc[6], t_wolf *wolf);

int					ft_get_color(int r, int g, int b);
int					ft_get_color_fog(int color, int fog);
int					color_gradient(int cs, int ce, double value);

Uint32				**ft_read_ppm(int fd, t_wolf *wolf);

void				ft_fill_tex(int index, SDL_Surface *sf, t_wolf *wolf);

int					a_is_left(double angle);
int					a_is_up(double angle);
int					get_closer_h(double pos[2], t_ray *ray);
int					get_closer_v(double pos[2], t_ray *ray);
double				ft_raylen(double *r, double *p);

void				ray_cast(double pos[2], t_ray *ray, t_wolf *wolf);

void				draw_minimap(t_wolf *wolf);

void				ft_draw(t_wolf *wolf);
void				ft_update(t_wolf *wolf);

void				ft_exit(t_wolf *wolf);
void				error_handler(int error, t_wolf *wolf);

#endif
