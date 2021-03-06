/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 10:46:15 by vludan            #+#    #+#             */
/*   Updated: 2017/11/06 13:21:11 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bzero(void *s, size_t n)
{
	int		x;
	int		y;

	x = n;
	y = 0;
	while ((y < x) && (x != 0))
	{
		*(unsigned char*)s++ = 0;
		y++;
	}
}
