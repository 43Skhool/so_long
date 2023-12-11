/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:24:31 by maceccar          #+#    #+#             */
/*   Updated: 2023/10/13 20:48:15 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lnb;

	lnb = n;
	if (fd < 0)
		return ;
	if (lnb < 0)
	{
		ft_putchar_fd('-', fd);
		lnb = -lnb;
	}
	if (lnb >= 10)
	{
		ft_putnbr_fd(lnb / 10, fd);
		lnb = lnb % 10;
	}
	ft_putchar_fd(lnb + 48, fd);
}
