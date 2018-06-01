/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:37:33 by schaaban          #+#    #+#             */
/*   Updated: 2018/06/01 15:28:16 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			get_img_size(int *w, int *h, char *s)
{
	int		space;
	int		i;

	space = 0;
	i = -1;
	while (s[++i])
	{
		if (ft_isdigit(s[i]))
			continue;
		else if (!ft_isdigit(s[i]) && s[i] == ' ' && i != 0)
		{
			space = i;
			s[i] = '\0';
			*w = ft_atoi(s);
			s[i] = ' ';
		}
		else
			return (0);
	}
	*h = ft_atoi(s + space + 1);
	return (1);
}

Uint32				**ft_read_ppm(int fd, t_wolf *wolf)
{
	Uint32		**res;
	char		*s;
	int			ret;
	int			line;
	int			i;
	int			j;
	int			c;
	int			size[2];

	line = -1;
	i = 0;
	j = -1;
	c = 0;
	while ((ret = get_next_line(fd, &s)) > 0)
	{
		line++;
		if (line == 0)
		{
			if (ft_strcmp(s, "P3") != 0)
			{
				ft_strdel(&s);
				error_handler(W_ERROR_TEX, wolf);
			}
		}
		else if (line == 1)
		{
			if (s[0] != '#')
			{
				ft_strdel(&s);
				error_handler(W_ERROR_TEX, wolf);
			}
		}
		else if (line == 2)
		{
			if (!get_img_size(&size[0], &size[1], s))
			{
				ft_strdel(&s);
				error_handler(W_ERROR_TEX, wolf);
			}
			if (!(res = (Uint32**)malloc(sizeof(Uint32*) * (size[1] + 1))))
			{
				ft_strdel(&s);
				error_handler(W_ERROR_MALLOC, wolf);
			}
			int k = -1;
			int l = -1;
			while (++k < size[1])
			{
				if (!(res[k] = (Uint32*)malloc(sizeof(Uint32) * size[0])))
				{
					ft_strdel(&s);
					error_handler(W_ERROR_MALLOC, wolf);
				}
				l = -1;
				while (++l < size[0])
					res[k][l] = 0;
			}
			res[k] = NULL;
		}
		else if (line == 3)
		{
			if (ft_strcmp(s, "255") != 0)
			{
				ft_strdel(&s);
				error_handler(W_ERROR_TEX, wolf);
			}
		}
		else
		{
			c = (line - 4) % 3;
			j += (c == 0) ? 1 : 0;
			if (j >= size[0])
				if (++i + (j = 0) >= size[1])
					break;
			if (!ft_str_isdigit(s))
			{
				ft_strdel(&s);
				error_handler(W_ERROR_TEX, wolf);
			}
			res[i][j] += (ft_atoi(s) << abs((c * 8) - 16));
		}
		ft_strdel(&s);
	}
	return (res);
}
