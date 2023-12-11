/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:35:05 by lebartol          #+#    #+#             */
/*   Updated: 2023/10/11 18:11:34 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*res;
	char	check;

	check = (char)c;
	res = NULL;
	while (*str)
	{
		if (*str == check)
			res = (char *)str;
		str++;
	}
	if (*str == check)
		res = (char *)str;
	return (res);
}
