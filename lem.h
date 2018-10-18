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

#ifndef LEM_H
# define LEM_H
# define BUFF_SIZE 1000

# include <stdlib.h>
# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct		s_lst
{
	char			*buff;
	int				ds;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_var
{
	char			colors;
	char			rlc;
	char			paths;
	char			map;
	char			leaks;
	int				x;
	int				ants;
	char			**lines;
}					t_var;

typedef struct		s_room
{
	char			*name;
	int				key;
	int				avail;
	int				x;
	int				y;
	int				dist;
	void			*father;
	struct s_room	*next;
	char			**links;
}					t_room;

int					get_next_line(const int fd, char **line);
t_room				*lem_parse(t_room *s);
int					lem_error(void);
t_room				*lem_check_4(t_room *pool);
t_room				*room_parse(char *line, t_room *s);
t_room				*room_key(int key, t_room *s);
t_room				*link_parse(char **line, t_room *s);
t_room				*room_maker(char *line, int key, t_room *s);
t_room				*room_create(char *line, int key, t_room *s);
int					room_name_cmp(char *line, char *line2, char c);
int					room_create_legitcoords(char *line, t_room *new);
int					room_create_valid_pattern(char *line);
t_room				*room_link(char *line, t_room *s);
int					room_link_validation(char *line, t_room *s);
t_room				*room_link_add(char *line, t_room *s, int c);
char				*room_link_nv(char *line);
int					lem_alg(t_room *s);
t_room				*path_search(t_room *pool);
t_room				*queue_take(t_room *pool, t_room **queue);
t_room				**queue_make(t_room *current, t_room *pool, t_room **queue);
void				path_saver(t_room *pool, t_room *path);
void				ants_prepare(t_room *pool);
void				ants_go(t_room *pool, t_room **arr);
int					lem_valid(t_room **pool);
int					ants_go_full(t_room *pool, t_room **arr,
					t_room *tmp2, int x, int y);
void				lem_free(t_room *s);
int					room_cmp(char *s1, char *s2, char c);
t_room				**queue_make_cycle(t_room *crnt, t_room *pool,
					t_room **queue, int x);
void				ants_go_step(int x, int y, t_room **arr,
					t_room *pool);
void				lem_map_arr(char *line);
void				printroom(t_room *s);
void				printmap(void);
int					ants_go_step_start(t_room **arr,
					t_room *tmp2, int x, int y);

#endif
