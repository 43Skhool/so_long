/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by maceccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:14 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "corekit.h"

int		ft_putptr(unsigned long lnb, char *base);

int		ft_is_in(char c, const char *ptr);

int		ft_putchar(char c);

int		ft_putstr(const char *str);

int		ft_putnbr(long int nb);

int		ft_printf(const char	*format, ...);

int		ft_putbase(unsigned int nb, char *base);

int		ft_unsignedputnbr(int n);

#endif
