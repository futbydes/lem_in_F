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

struct s_var	*vars;

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
	ft_printf("%s\n", "ERROR");
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

void			lem_free(t_room *s)
{
	int			x;
	t_room		*temp;

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

t_room			*lem_parse(t_room *s)
{
	char		*line;
	t_room		*res;
	int			exit;

	exit = 0;
	get_next_line(0, &line);
	lem_parse_ants(line);
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
