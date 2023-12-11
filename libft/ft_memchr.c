/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:49:09 by lebartol          #+#    #+#             */
/*   Updated: 2023/10/11 16:46:50 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*res;
	unsigned int	i;

	i = 0;
	res = (unsigned char *)str;
	while (i < n)
	{
		if (res[i] == (unsigned char)c)
		{
			return (res + i);
		}
		i++;
	}
	return (NULL);
}
