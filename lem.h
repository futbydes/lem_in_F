/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 11:06:49 by vludan            #+#    #+#             */
/*   Updated: 2018/10/09 11:07:58 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# define BUFF_SIZE 1000

# include <stdlib.h>
# include "libft/libft.h"

typedef struct 		s_lst
{
	int				ds;
	char			*buff;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_room
{
	char			*name;
	int				key;
	int				avail;
	void			*father;
	int				x;
	int				y;
	int 			dist;
	struct s_room	*next;
	char			**links;
}					t_room;

int					get_next_line(const int fd, char **line);
#include <stdio.h>
t_room				*lem_parse(t_room *s);
int 				lem_error(void);
t_room				*lem_check_4(t_room *pool);
t_room				*room_parse(char *line, t_room *s);
t_room				*room_key(char *line, int key, t_room *s);
t_room				*link_parse(char *line, t_room *s);
t_room				*room_maker(char *line, int key, t_room *s);
t_room				*room_create(char *line, int key, t_room *s);
int					room_create_legitcoords(char *line, t_room *new);
int					room_create_valid_pattern(char *line);
t_room				*room_link(char *line, t_room *s);
int					room_link_validation(char *line, t_room *s);
t_room				*room_link_add(char *line, t_room *s, int c);
char				*room_link_invert(char *line);
int					lem_alg(t_room *s);
t_room				*path_search(t_room *pool);
t_room				*queue_take(t_room *pool, t_room **queue);
t_room				**queue_make(t_room *current, t_room *pool, t_room **queue);
void				path_saver(t_room *pool, t_room *path);
void				ants_on_paths(t_room *pool);
void				ants_go(t_room *pool, t_room **arr, int x);
int 				lem_valid(t_room **pool);
int 				ants_go_full(t_room *pool, t_room **arr, t_room *tmp2, int x, int y);




void				printroom(t_room *s);

#endif