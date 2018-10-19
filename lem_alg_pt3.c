/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:09:37 by vludan            #+#    #+#             */
/*   Updated: 2018/10/10 18:09:57 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem.h"

extern struct s_var *vars;

t_room		**queue_make_cycle(t_room *crnt, t_room *pool, t_room **queue,
	int x)
{
	int		y;
	t_room	*temp;

	y = 0;
	while (queue[y] != 0)
		y++;
	while (crnt->links && crnt->links[x] != 0)
	{
		temp = pool;
		while (temp && ft_strcmp(crnt->links[x], temp->name))
			temp = temp->next;
		if (temp && temp->avail == 0)
		{
			temp->avail = 1;
			temp->father = crnt;
			temp->dist = crnt->dist + 1;
			queue[y] = temp;
			y++;
		}
		x++;
	}
	queue[y] = 0;
	return (queue);
}

void		printroom(t_room *s)
{
	int		x;

	while (s != 0)
	{
		x = 0;
		ft_printf(L_GREEN "  ROOM_NAME: %s\n" RESET,
			s->name);
		ft_printf(DARKGREY "ROOM_COORDS: %d %d\n"
			RESET, s->x, s->y);
		if (s->links != 0)
		{
			ft_printf(" ROOM_LINKS:");
			while (s->links[x] != 0)
			{
				ft_printf(" %s", s->links[x]);
				x++;
			}
			ft_printf("\n");
		}
		s = s->next;
	}
	ft_printf("\n");
}

void		printmap(void)
{
	int		x;

	x = -1;
	if (vars->colors == 0)
	{
		ft_printf("%d\n", vars->ants);
		while (vars->lines && vars->lines[++x] != 0)
			ft_printf("%s\n", vars->lines[x]);
	}
	else
	{
		ft_printf(L_GREEN "%d\n" RESET, vars->ants);
		while (vars->lines && vars->lines[++x] != 0)
		{
			if (!ft_strncmp(vars->lines[x], "##", 2))
				ft_printf(L_GREEN "%s\n" RESET, vars->lines[x]);
			else if (!ft_strncmp(vars->lines[x], "#", 1))
				ft_printf(DARKGREY "%s\n" RESET, vars->lines[x]);
			else
				ft_printf(CYAN "%s\n" RESET, vars->lines[x]);
		}
	}
	ft_printf("\n");
}
