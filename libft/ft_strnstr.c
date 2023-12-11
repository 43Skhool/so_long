/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:22:58 by lebartol          #+#    #+#             */
/*   Updated: 2023/10/13 14:38:32 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	j = 0;
	little_len = ft_strlen(little);
	if (little_len < 1)
		return ((char *)big);
	while (i < len && big[i])
	{
		while (big[i + j] == little[j])
		{
			j++;
			if ((i + j) > len)
				return (NULL);
			if (j == little_len)
				return ((char *)big + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
