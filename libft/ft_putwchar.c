/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:02:56 by rtulchiy          #+#    #+#             */
/*   Updated: 2017/12/08 19:41:38 by rtulchiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_bytelen(int a)
{
	int		i;

	i = 0;
	while (a && ++i)
		a /= 2;
	if (i <= 7)
		i = 1;
	else if (i <= 11)
		i = 2;
	else if (i <= 16)
		i = 3;
	else
		i = 4;
	return (i);
}

static void	first_macros(int *chars, int numb, int bytes, int *a)
{
	int		n;

	n = 8 - (bytes + 1);
	while (n--)
	{
		chars[numb] <<= 1;
		chars[numb] |= (a & 1);
		a >>= 1;
	}
	chars[numb] <<= (bytes + 1);
	bytes = ft_pow(2, bytes) - 1;
	chars[numb] |= bytes;
	chars[numb] = ft_revbits(chars[numb]);
}

static void	sec_macros(int *chars, int numb, int *a)
{
	int		n;

	n = 6;
	while (n--)
	{
		chars[numb] <<= 1;
		chars[numb] |= (*a & 1);
		*a >>= 1;
	}
	chars[numb] <<= 2;
	chars[numb] |= 1;
	chars[numb] = ft_revbits(chars[numb]);
}

static void	fillbyte(int *chars, int numb, int a)
{
	int		bytes;
	int		i;

	bytes = numb;
	while (--numb + 1)
	{
		if (numb)
			sec_macros(chars, numb, &a);
		else
			first_macros(chars, nums, bytes, &a);
	}
}

void		ft_putwchar(wchar_t c)
{
	int		*chars;
	int		num_byte;
	int		a;
	int		i;

	chars = (int*)ft_memalloc(4 * sizeof(int));
	a = (int)c;
	if ((num_byte = ft_bytelen(a)) == 1)
		chars[0] = (unsigned char)a;
	else
		fillbyte(chars, num_byte, a);
	i = 0;
	while (i < num_byte)
		write(1, &chars[i++], 1);
}
