/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 11:06:11 by vludan            #+#    #+#             */
/*   Updated: 2018/10/15 15:44:06 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

extern struct s_var *vars;

void				lem_parse_ants(char *line)
{
	int				x;

	x = 0;
	while (line[x] && ft_isdigit(line[x]))
		x++;
	if (!line[x])
		vars->ants = ft_atoi(line);
	else
		vars->ants = -1;
}

t_room				*room_parse(char *line, t_room *s)
{
	static int		st;
	static int		e;

	lem_map_arr(line);
	if ((ft_strcmp("##colors", line) == 0 && vars->colors++) ||
		(ft_strcmp("##rlc", line) == 0 && vars->rlc++) ||
		(ft_strcmp("##paths", line) == 0 && vars->paths++) ||
		(ft_strcmp("##map_off", line) == 0 && vars->map++) ||
		(ft_strcmp("##leaks", line) == 0 && vars->leaks++))
		return (s);
	else if (ft_strcmp("##start", line) == 0 && ++st && st < 2)
		return (room_key(1, s));
	else if (ft_strcmp("##end", line) == 0 && ++e && e < 2)
		return (room_key(2, s));
	else
		return (room_maker(line, 0, s));
}

t_room				*room_key(int key, t_room *s)
{
	char			*lin;

	get_next_line(0, &lin);
	lem_map_arr(lin);
	if (*lin == 0 || !room_create_valid_pattern(lin) ||
		!ft_strncmp("#", lin, 1))
	{
		free(lin);
		return (0);
	}
	else
	{
		s = room_maker(lin, key, s);
		free(lin);
		return (s);
	}
}

t_room				*link_parse(char **line, t_room *s)
{
	t_room			*x;

	lem_map_arr(*line);
	if (!ft_strcmp("##start", *line) || !ft_strcmp("##end", *line))
		return (0);
	else if (!ft_strncmp(*line, "#", 1))
		return (s);
	else if (ft_strchr(*line, '-'))
	{
		x = room_link(*line, s);
		if (x != 0)
		{
			*line = room_link_nv(*line);
			x = room_link(*line, s);
		}
		if (x != 0)
			return (s);
		else
			return (0);
	}
	else
		return (0);
}

char				*room_link_nv(char *line)
{
	char			*new;

	new = ft_memalloc(ft_strlen(line) + 1);
	ft_strcpy(new, line + ft_strnlen(line, '-') + 1);
	ft_memmove(new + ft_strlen(new), "-", 1);
	ft_memmove(new + ft_strlen(new), line, ft_strnlen(line, '-'));
	free(line);
	return (new);
}
