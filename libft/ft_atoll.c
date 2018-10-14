/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:45:50 by vludan            #+#    #+#             */
/*   Updated: 2018/10/09 15:56:32 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long			ft_atoll(const char *str)
{
	long long int		n;
	int					x;
	int					c;

	n = 0;
	c = 1;
	x = 0;
	while (ft_iswhitespaces(str[x]))
		x++;
	if (str[x] == '-')
		c = -1;
	if ((str[x] == '+') || (str[x] == '-'))
		x++;
	while ((str[x] != '\0') && (str[x] >= 48) && (str[x] <= 57))
	{
		n = (n * 10 + str[x] - 48);
		x++;
	}
	return ((long long)(n * c));
}

