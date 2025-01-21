/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:52:09 by mskerba           #+#    #+#             */
/*   Updated: 2021/11/18 22:04:13 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int	i;

	i = nb;
	if (i < 0)
	{
		ft_putstr_fd("-", fd);
		i = -i;
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
	}
	ft_putchar_fd(i % 10 + '0', fd);
}
