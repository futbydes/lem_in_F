/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:09:50 by vludan            #+#    #+#             */
/*   Updated: 2017/12/20 15:57:53 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	int		x;
	int		y;
	int		*temp;

	y = len;
	x = 0;
	temp = b;
	while (x++ < y)
		*(unsigned char*)b++ = (unsigned char)c;
	return (temp);
}
