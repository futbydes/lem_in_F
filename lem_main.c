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

int				g_ants;

int				main(void)
{
	t_room		*s;
	t_room		*temp;

	s = ft_memalloc(sizeof(t_room));
		temp = s;
	s = lem_parse(s);
	s = lem_check_4(s);
	if (s == 0)
	{
			//lem_free(temp);
	//	system("leaks lem-in");
		return (lem_error());
	}
	printroom(s->next);
	lem_alg(s->next);
//	lem_free(temp->next);
//	system("leaks lem-in");
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
	int 		s;
	int 		e;

	s = 0;
	e = 0;
	tmp = pool;
	while (tmp)
	{
		tmp->key == 1? s++ : 0;
		tmp->key == 2? e++ : 0;
		tmp = tmp->next;
	}
	if (s != 1 || e != 1)
		return (0);
	else
		return (pool);
}

void				lem_free(t_room *s)
{
	int 			x;
	t_room			*temp;

	x = 0;
	temp = s;
	while (s != 0)
	{
		if (s->name != 0)
			free(s->name);
		while (s->links && s->links[x] != 0)
		{
			free(s->links[x]);
			x++;
		}
		if (x != 0)
			free(s->links[x]);
		s = s->next;
	}
}

t_room				*lem_parse(t_room *s)
{
	char		*line;
	t_room		*res;
	int			exit;

	exit = 0;
	get_next_line(0, &line);
	g_ants = ft_atoi(line);
	free(line);
	if (g_ants < 1)
		return (0);
	res = s;
	while (res != 0 && get_next_line(0, &line) > 0)
	{
		s = res;
		if ((ft_strchr(line, ' ') || !ft_strncmp("#", line, 1)) && !exit)
		{
			res = room_parse(line, s);
		}
		else 
		{
			res = link_parse(&line, s);
			exit = 1;
		}
	//	line != 0 ? free(line) : 0;
	}
	return (s);
}

t_room				*room_parse(char *line, t_room *s)
{
	static int		st;
	static int		e;

	if (ft_strcmp("##start", line) == 0 && ++st && st < 2)
		return (room_key(line, 1, s));
	else if (ft_strcmp("##end", line) == 0 && ++e && e < 2)
		return (room_key(line, 2, s));
	else 
		return (room_maker(line, 0, s));
}

t_room			*room_key(char *line, int key, t_room *s)
{
	free(line);
	get_next_line(0, &line);
	if (*line == 0 || !room_create_valid_pattern(line) ||
		!ft_strncmp("#", line, 1))
		return (0);
	else
		return (room_maker(line, key, s));
}

t_room			*link_parse(char **line, t_room *s)
{
	t_room		*x;

	if (!ft_strcmp("##start", *line) || !ft_strcmp("##end", *line))
		return (0);
	else if (!ft_strncmp(*line, "#", 1))
		return (s);
	else if (ft_strchr(*line, '-'))
	{
		x = room_link(*line, s);
		if (x != 0)
		{
			*line = room_link_invert(*line);
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

char			*room_link_invert(char *line)
{
	char		*new;


	new = ft_memalloc(ft_strlen(line) + 1);
	ft_strcpy(new, line + ft_strnlen(line, '-') + 1);
	ft_memmove(new + ft_strlen(new), "-", 1);
	ft_memmove(new + ft_strlen(new), line, ft_strnlen(line, '-'));
//	free(line);
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
	while (temp != 0 && s != 0)
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

int 		room_cmp(char *s, char *s2, char c)
{
	int 	x;

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
	temp = ft_strchr(line,'-');
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
	while (temp != 0 && c++) //c + 1 for cycle if c == 0 its stops 
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
	s->links[x] = ft_strcpy(s->links[x], (line + ft_strnlen(line, '-') + 1));
	s->links[x + 1] = 0;
	return (temp);
}

// FIRST EL OF ARR IS 0 , NEED TO CHECK FOR 0 ROOM FOR BUG

t_room			*room_maker(char *line, int key, t_room *s)
{
	if (!ft_strncmp("L", line, 1) || !ft_strcmp("##start", line) ||
		!ft_strcmp("##end", line) ||
		ft_memchr(line, '-', ft_strnlen(line, ' ')))
	{
		return (0);
	}
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
	long long 	y;

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

void			printroom(t_room *s)
{
	int			x;

	while (s != 0)
	{
		x = 0;
		printf("  ROOM_NAME: %s\n", s->name);
		printf("ROOM_COORDS: %d %d\n", s->x, s->y);
		if (s->links != 0)
		{
			printf(" ROOM_LINKS:");
			while (s->links[x] != 0)
			{
				printf(" %s", s->links[x]);
				x++;
			}
			printf("\n");
		}
		s = s->next;
	}
}
