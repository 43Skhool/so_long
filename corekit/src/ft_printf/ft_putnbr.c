/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/24 13:56:23 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putnbr(long int nb)
{
	int	i;

	i = 0;
	if (nb >= 10)
	{
		i += putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10)
		i += ft_putchar(nb + 48);
	return (i);
}

int	ft_putnbr(long int nb)
{
	int		i;
	long	lnb;

	i = 0;
	lnb = nb;
	if (nb < 0)
	{
		i += ft_putchar('-');
		lnb = -lnb;
	}
	if (lnb >= 10)
	{
		i += putnbr(lnb / 10);
		lnb = lnb % 10;
	}
	if (lnb < 10)
		i += ft_putchar(lnb + 48);
	return (i);
}
