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
