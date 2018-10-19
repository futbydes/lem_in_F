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

int				room_cmp(char *s, char *s2, char c)
{
	int			x;

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
		ft_strnlen(line, '-') + 1) + 1, ' ') + 2);
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
