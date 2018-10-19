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

int				lem_alg(t_room *s)
{
	t_room		*path;
	int			err;

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

void			ants_go(t_room *pool, t_room **arr)
{
	while (lem_valid(arr))
	{
		ants_go_step(0, 0, arr, pool);
		ft_printf("\n");
	}
}

void			ants_go_step(int x, int y, t_room **arr, t_room *pool)
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

int				ants_go_step_start(t_room **arr, t_room *tmp2, int x, int y)
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
