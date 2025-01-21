/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 06:01:30 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/22 16:14:31 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t	dstsize)
{
	unsigned int	src_len;
	unsigned int	dest_len;
	unsigned int	i;

	dest_len = ft_strlen(dest);
	src_len = 0;
	src_len = ft_strlen(src);
	if (dest_len >= dstsize)
		return (dstsize + src_len);
	if ((dstsize == 0 && !dest) || dstsize == 0)
	{
		return (src_len);
	}
	i = 0;
	while (src[i] && dest_len + i < (dstsize - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (src_len + dest_len);
}
