/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:55 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/25 15:16:27 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

static	char	**chek_and_fill(char **t, char const *s, char c)
{
	int	i;
	int	count;
	int	star;

	i = 0;
	count = 0;
	while (s[i])
	{
		star = i;
		if (s[i++] == c)
			continue ;
		while (s[i] != c && s[i])
			i++;
		t[count] = ft_substr(s, star, i - star);
		if (!t[count])
		{
			while (--count)
				free(t[count]);
			free(t);
		}
		count++;
	}
	t[count] = 0;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		count;

	if (s == 0)
		return (0);
	count = set_count(s, c);
	t = (char **)malloc(sizeof(char *) * (count + 1));
	if (t == NULL)
		return (0);
	return (chek_and_fill(t, s, c));
}
