/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 00:14:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/05/09 21:51:35 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		parser_size_check(char **lines, t_wolf *wolf)
{
	int		last_width;
	int		i;
	int		j;

	i = -1;
	last_width = 0;
	wolf->map_w = 0;
	while (lines[++i] != NULL)
	{
		if (last_width != wolf->map_w && i != 0)
			return (0);
		wolf->map_w = 0;
		j = -1;
		while (lines[i][++j])
		{
			if ((ft_isdigit(lines[i][j]) && j % 2 == 0))
				wolf->map_w++;
			else if (lines[i][j] != ' ')
				return (0);
		}
		last_width = wolf->map_w;
	}
	wolf->map_h = i;
	return ((wolf->map_w < 3 || wolf->map_h < 3) ? 0 : 1);
}

static int		parser_fill_line(char *line, int map_i, t_wolf *wolf)
{
	int		i;
	int		i_s;

	i = -1;
	i_s = 0;
	while (++i < wolf->map_w)
	{
		wolf->map[map_i][i] = line[i_s] - '0';
		i_s += 2;
	}
	if (line[i_s - 1] != '\0')
		return (0);
	i = -1;
	if (map_i == 0 || map_i == wolf->map_h - 1)
	{
		while (++i < wolf->map_w)
			if (wolf->map[map_i][i] == 0)
				return (0);
	}
	else
		if (wolf->map[map_i][0] == 0 || wolf->map[map_i][wolf->map_w - 1] == 0)
			return (0);
	return (1);
}

static int		parser_fill_map(char **lines, t_wolf *wolf)
{
	int		i;
	int		line_res;

	i = -1;
	while (lines[++i] != NULL)
	{
		if (!(wolf->map[i] = (int*)malloc(sizeof(int) * wolf->map_w)))
			return (-1);
		if ((line_res = parser_fill_line(lines[i], i, wolf)) < 1)
		{
			wolf->map[i] = NULL;
			return (line_res);
		}
	}
	wolf->map[i] = NULL;
	return (1);
}

static int		parser_getmap(char *file_str, t_wolf *wolf)
{
	char	**lines;
	int		parse_res;

	if (!(lines = ft_strsplit(file_str, '\n')))
		return (-1);
	if ((parse_res = parser_size_check(lines, wolf)) < 1)
	{
		lines ? ft_a2ddel((void***)&lines) : 0;
		return (parse_res);
	}
	if (!(wolf->map = (int**)malloc(sizeof(int*) *
		(wolf->map_h + 1))))
	{
		lines ? ft_a2ddel((void***)&lines) : 0;
		return (-1);
	}
	if ((parse_res = parser_fill_map(lines, wolf)) < 1)
	{
		lines ? ft_a2ddel((void***)&lines) : 0;
		return (parse_res);
	}
	lines ? ft_a2ddel((void***)&lines) : 0;
	return (1);
}

void			parse_file(t_wolf *wolf)
{
	char	*file_str;
	char	*file_line;
	int		res;
	int 	ret;

	file_str = NULL;
	while ((ret = get_next_line(wolf->fd, &file_line)) > 0)
	{
		if (!(file_str = ft_join("110", file_str, file_line, "\n")))
			error_handler(W_ERROR_MALLOC, wolf);
	}
	(ret < 0) ? error_handler(W_ERROR_READ, wolf) : 0;
	!file_str ? error_handler(W_ERROR_MALLOC, wolf) : 0;
	res = parser_getmap(file_str, wolf);
	file_str ? ft_memdel((void**)&file_str) : 0;
	(res < 1) ? error_handler((res == -1) ?
		W_ERROR_MALLOC : W_ERROR_FILE, wolf) : 0;
}
