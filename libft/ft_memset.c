/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:43:50 by maceccar          #+#    #+#             */
/*   Updated: 2023/10/11 16:54:32 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = dest;
	i = 0;
	while (i < count)
	{
		tmp[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
