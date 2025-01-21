/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:09:45 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/25 16:18:55 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_count(long int n)
{
	int	i;

	i = 0;
	while (n >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	is_neg(long int *n)
{
	int	neg;

	neg = 0;
	if (*n < 0)
	{
		neg = 1;
		*n *= -1;
	}
	return (neg);
}

static int	count(long int n)
{
	int	k;
	int	i;

	i = 1;
	k = num_count(n) - 1;
	while (k > 0)
	{
		i *= 10;
		k--;
	}
	return (i);
}

static char	*print_number(char *dst, int i, long int n, int s)
{	
	int	k;

	k = count(n);
	while (++i < s)
	{
		dst[i] = (n / k) + 48;
		n %= k;
		k /= 10;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int c)
{
	char		*dst;
	int			neg;
	int			x;
	long int	n;

	n = c;
	if (n == 0)
	{
		dst = malloc(2);
		dst[0] = '0';
		dst[1] = '\0';
		return (dst);
	}
	neg = is_neg(&n);
	x = num_count(n);
	dst = malloc(sizeof(char) * (x + neg + 1));
	if (!dst)
		return (0);
	if (neg == 1)
		dst[0] = '-';
	return (print_number(dst, neg - 1, n, x + neg));
}
