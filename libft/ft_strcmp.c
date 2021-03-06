/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vludan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:41:16 by vludan            #+#    #+#             */
/*   Updated: 2017/11/06 13:27:14 by vludan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int				x;

	x = 0;
	while ((s1[x] == s2[x]) && ((s1[x] != '\0') || (s2[x] != '\0')))
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
