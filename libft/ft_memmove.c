/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 06:01:06 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/25 16:18:38 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	unsigned int	i;

	if (src == 0 && dst == 0)
		return (0);
	i = -1;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d > s)
	{
		while (0 < len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
		while (++i < len)
			d[i] = s[i];
	return (dst);
}
