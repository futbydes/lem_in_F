#include <stdio.h>

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