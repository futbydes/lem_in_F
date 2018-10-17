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

struct g_var	*vars;

int				main(void)
{
	t_room		*s;
	t_room		*temp;
	int			l;

	s = ft_memalloc(sizeof(t_room));
	vars = ft_memalloc(sizeof(t_var));
	temp = s;
	s = lem_parse(s);
	l = vars->leaks;
	s = lem_check_4(s);
	if (s == 0)
	{
		lem_free(temp);
		l != 0 ? system("leaks lem-in") : 0;
		return (lem_error());
	}
	lem_alg(s->next);
	lem_free(s->next);
	free(s);
	l != 0 ? system("leaks lem-in") : 0;
	return (0);
}

int				lem_error(void)
{
	printf("%s\n", "ERROR");
	return (1);
}

t_room			*lem_check_4(t_room *pool)
{
	t_room		*tmp;
	int			s;
	int			e;

	s = 0;
	e = 0;
	tmp = pool;
	while (tmp)
	{
		tmp->key == 1 ? s++ : 0;
		tmp->key == 2 ? e++ : 0;
		tmp = tmp->next;
	}
	if (s != 1 || e != 1)
		return (0);
	else
		return (pool);
}

void				lem_free(t_room *s)
{
	int				x;
	t_room			*temp;

	while (s != 0)
	{
		x = 0;
		temp = s;
		if (s->name != 0)
			free(s->name);
		while (s->links && s->links[x] != 0)
		{
			free(s->links[x]);
			x++;
		}
		free(s->links);
		s = s->next;
		free(temp);
	}
	x = -1;
	while (vars->lines && vars->lines[++x] != 0)
		free(vars->lines[x]);
	free(vars->lines);
	free(vars);
}

t_room				*lem_parse(t_room *s)
{
	char		*line;
	t_room		*res;
	int			exit;

	exit = 0;
	get_next_line(0, &line);
	vars->ants = ft_atoi(line);
	free(line);
	if (vars->ants < 1 || vars->ants > 1000000)
		return (0);
	res = s;
	while (res != 0 && get_next_line(0, &line) > 0)
	{
		s = res;
		if ((ft_strchr(line, ' ') || !ft_strncmp("#", line, 1)) && !exit)
			res = room_parse(line, s);
		else
		{
			res = link_parse(&line, s);
			exit = 1;
		}
		free(line);
	}
	res != 0 ? free(line) : 0;
	return (s);
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

t_room			*room_key(int key, t_room *s)
{
	char		*lin;

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

t_room			*link_parse(char **line, t_room *s)
{
	t_room		*x;

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

char			*room_link_nv(char *line)
{
	char		*new;

	new = ft_memalloc(ft_strlen(line) + 1);
	ft_strcpy(new, line + ft_strnlen(line, '-') + 1);
	ft_memmove(new + ft_strlen(new), "-", 1);
	ft_memmove(new + ft_strlen(new), line, ft_strnlen(line, '-'));
	free(line);
	return (new);
}

t_room			*room_link(char *line, t_room *s)
{
	int			temp;
	t_room		*temp2;
	int			x;

	temp = 1;
	temp2 = s;
	x = 0;
	if (!room_link_validation(line, s->next))
		return (0);
	while (temp != 0 && s->next != 0)
	{
		s = s->next;
		temp = room_cmp(s->name, line, '-');
		x++;
	}
	if (!temp)
	{
		if (!room_link_add(line, s, x))
			return (0);
		return (temp2);
	}
	else
		return (0);
}

int			room_cmp(char *s, char *s2, char c)
{
	int		x;

	x = 0;
	while (s[x] == s2[x] && s[x] != 0 && s2[x] != 0)
		x++;
	if (s2[x] == c && s[x] == '\0')
		return (0);
	else
		return (1);
}

int				room_link_validation(char *line, t_room *s)
{
	char		*temp;
	t_room		*tmp;
	int			x;

	x = 0;
	tmp = s;
	temp = ft_strchr(line, '-');
	temp += 1;
	if (ft_strchr(temp, '-'))
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(temp, tmp->name))
			x++;
		tmp = tmp->next;
	}
	if (x == 1)
		return (1);
	else
		return (0);
}

t_room			*room_link_add(char *line, t_room *s, int c)
{
	int			x;
	t_room		*temp;

	temp = s;
	while (temp != 0 && c++)
		temp = temp->next;
	temp = s;
	x = 0;
	if (s->links == 0)
		s->links = ft_memalloc(8 * ((c - 1) + 1));
	while (s->links[x] != 0 && ft_strcmp(line +
		ft_strnlen(line, '-') + 1, s->links[x]))
		x++;
	if (s->links[x] != 0 || !ft_strcmp(ft_strchr(line, '-') + 1, s->name))
		return (temp);
	s->links[x] = ft_memalloc(ft_strnlen((line +
		ft_strnlen(line, '-') + 1) + 1, ' '));
	ft_strcpy(s->links[x], (line + ft_strnlen(line, '-') + 1));
	s->links[x + 1] = 0;
	return (temp);
}

t_room			*room_maker(char *line, int key, t_room *s)
{
	if (!ft_strncmp("L", line, 1) || !ft_strcmp("##start", line) ||
		!ft_strcmp("##end", line) ||
		ft_memchr(line, '-', ft_strnlen(line, ' ')))
		return (0);
	else if (!ft_strncmp("#", line, 1))
		return (s);
	else
	{
		s = room_create(line, key, s);
		return (s);
	}
}

t_room			*room_create(char *line, int key, t_room *s)
{
	t_room		*temp;
	t_room		*new;

	temp = s;
	while (s->next != 0)
	{
		s = s->next;
		if (!room_cmp(s->name, line, ' '))
			return (0);
	}
	new = ft_memalloc(sizeof(t_room));
	if (room_create_legitcoords(line, new))
	{
		free(new);
		return (0);
	}
	s->next = new;
	s->links = 0;
	new->next = 0;
	new->father = 0;
	new->name = ft_memalloc(ft_strnlen(line, ' ') + 1);
	new->name = ft_memcpy(new->name, line, ft_strnlen(line, ' '));
	new->key = key;
	return (temp);
}

int				room_create_legitcoords(char *line, t_room *new)
{
	long long	n;
	long long	y;

	if (!room_create_valid_pattern(line))
		return (1);
	n = ft_atoll(line + ft_strnlen(line, ' ') + 1);
	y = ft_atoll(line + ((ft_strnlen(line, ' ') + 2) +
		ft_strnlen(line + (ft_strnlen(line, ' ') + 2), ' ')));
	if ((n > 2147483647) || (n < -2147483648) ||
		(y > 2147483647) || (y < -2147483648))
		return (1);
	new->x = (int)n;
	new->y = (int)y;
	return (0);
}

int				room_create_valid_pattern(char *line)
{
	int			s;
	char		*temp;

	temp = ft_strchr(line, ' ');
	s = 0;
	if (temp == 0)
		return (0);
	while (*temp != '\0')
	{
		temp += 1;
		if (*temp == '-' || *temp == '+')
			temp++;
		while (*temp != ' ' && *temp != '\0')
		{
			if (!ft_isdigit(*temp))
				return (0);
			temp++;
		}
		if (*temp == ' ')
			s++;
		if (s > 1 || s == 0)
			return (0);
	}
	return (1);
}

void			lem_map_arr(char *line)
{
	int			x;
	int			z;
	char		**temp;

	x = 0;
	z = -1;
	while (vars->lines && vars->lines[x] != 0)
		x++;
	temp = ft_memalloc(((x == 0 ? 1 : x) + 2) * 8);
	while (++z != x)
	{
		temp[z] = ft_memalloc(ft_strlen(vars->lines[z]) + 1);
		ft_strcpy(temp[z], vars->lines[z]);
	}
	temp[z] = ft_memalloc(ft_strlen(line) + 1);
	ft_strcpy(temp[z], line);
	temp[z + 1] = 0;
	if (x != 0)
	{
		z = -1;
		while (vars->lines[++z] != 0)
			free(vars->lines[z]);
		free(vars->lines);
	}
	vars->lines = temp;
}
