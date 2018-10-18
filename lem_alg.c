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

int			lem_alg(t_room *s)
{
	t_room	*path;
	int		err;

	path = s;
	err = 0;
	while (path)
	{
		path = path_search(s);
		if (path != 0)
		{
			err = 1;
			vars->paths != 0 ? ft_printf("PATH AVAIL: ") : 0;
			path_saver(s, path);
			vars->paths != 0 ? ft_printf("\n") : 0;
			path = path->father;
		}
	}
	if (err == 0)
		return (lem_error());
	vars->map != 0 ? 0 : printmap();
	vars->rlc != 0 ? printroom(s) : 0;
	ants_prepare(s);
	return (0);
}

void			ants_prepare(t_room *pool)
{
	int			x;
	t_room		*tmp;
	t_room		*path;
	t_room		*arr[vars->ants + 1];

	x = 0;
	path = pool;
	while (path)
	{
		tmp = path->father;
		if (tmp != 0 && path->key != 0 && tmp->key == 0)
			path->father = 0;
		path = path->next;
	}
	tmp = pool;
	while (tmp->key != 1)
		tmp = tmp->next;
	while (x != vars->ants + 1)
	{
		arr[x] = tmp;
		x++;
	}
	arr[x] = 0;
	ants_go(pool, arr);
}

void		ants_go(t_room *pool, t_room **arr)
{
	while (lem_valid(arr))
	{
		ants_go_step(0, 0, arr, pool);
		ft_printf("\n");
	}
}

void		ants_go_step(int x, int y, t_room **arr, t_room *pool)
{
	while (x < vars->ants)
	{
		if (arr[x] != 0 && arr[x]->key != 2 && arr[x]->links[y] != 0
			&& arr[x]->father == 0)
		{
			x = ants_go_step_start(arr, pool, x, y);
			y++;
		}
		else if (arr[x] != 0 && arr[x]->father != 0)
		{
			arr[x] = arr[x]->father;
			ft_printf("L%d-%s ", x + 1, arr[x]->name);
			if (arr[x]->key == 2)
				arr[x] = 0;
			x++;
		}
		else
			x++;
	}
}

int			ants_go_step_start(t_room **arr, t_room *tmp2, int x, int y)
{
	while (ft_strcmp(arr[x]->links[y], tmp2->name))
		tmp2 = tmp2->next;
	if (tmp2->avail > 1)
	{
		arr[x] = tmp2;
		ft_printf("L%d-%s ", x + 1, arr[x]->name);
		x++;
	}
	return (x);
}

int			lem_valid(t_room **pool)
{
	int		c;
	int		x;

	c = 0;
	x = 0;
	while (x < vars->ants)
	{
		if (pool[x] == 0)
			x++;
		else
		{
			if (pool[x]->key != 2)
				c++;
			x++;
		}
	}
	return (c);
}

void		path_saver(t_room *pool, t_room *path)
{
	t_room	*temp;

	temp = path->father;
	if ((path->key == 1 || path->key == 2)
		&& (temp->key == 1 || temp->key == 2))
	{
		path->avail = 3;
		temp->avail = 3;
		return ;
	}
	temp = pool;
	while (temp)
	{
		temp->avail < 3 ? temp->avail = 0 : 0;
		temp = temp->next;
	}
	while (path->father && path->dist != 0)
	{
		vars->paths != 0 ? ft_printf("%s ", path->name) : 0;
		if (path->key == 1 || path->key == 2)
			path->dist = 0;
		else
			path->avail = 3;
		path = path->father;
	}
}

t_room		*path_search(t_room *pool)
{
	t_room	**queue;
	t_room	*crnt;

	crnt = pool;
	queue = 0;
	while (crnt->key != 2)
		crnt = crnt->next;
	while (crnt && crnt->key != 1)
	{
		queue = queue_make(crnt, pool, queue);
		crnt->avail = 2;
		crnt = queue_take(pool, queue);
	}
	free(queue);
	if (crnt && crnt->key == 1)
		return (crnt);
	else
		return (0);
}

t_room		*queue_take(t_room *pool, t_room **queue)
{
	int		x;
	t_room	*temp;
	t_room	*ret;

	x = 0;
	ret = 0;
	temp = pool;
	while (ret != temp && queue[x])
	{
		temp = pool;
		while (temp && queue[x] != temp)
			temp = temp->next;
		if (temp->avail == 2)
			x++;
		else
			ret = temp;
	}
	if (!ret && queue[x] == 0)
		ret = 0;
	return (ret);
}

t_room		**queue_make(t_room *crnt, t_room *pool, t_room **queue)
{
	int		x;
	int		y;
	t_room	*temp;

	x = 0;
	y = 0;
	temp = pool;
	if (queue == 0)
	{
		while (temp && ++y)
			temp = temp->next;
		queue = ft_memalloc((y + 1) * 8);
	}
	return (queue_make_cycle(crnt, pool, queue, x));
}

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

void			printroom(t_room *s)
{
	int			x;

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

void			printmap(void)
{
	int			x;

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
