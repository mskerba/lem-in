/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 06:02:04 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/15 06:35:57 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*s, int c)
{
	int		i;
	int		n;
	char	*val;

	val = 0;
	i = 0;
	n = ft_strlen(s);
	while (i <= n)
	{
		if (s[i] == (char)c)
		{
			val = (char *)&s[i];
		}
		i++;
	}
	return (val);
}
