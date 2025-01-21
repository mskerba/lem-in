/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 08:11:16 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/22 14:29:09 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (j + i + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, i + 1);
	ft_strlcat(dst, s2, i + j + 1);
	return (dst);
}
