/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 06:00:59 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/16 11:14:53 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void	*src, size_t	n)
{
	char	*s;
	char	*d;

	if (!src && !dst)
		return (0);
	s = (char *)src;
	d = (char *)dst;
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}
