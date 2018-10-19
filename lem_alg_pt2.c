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
