/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:25:51 by maceccar          #+#    #+#             */
/*   Updated: 2024/02/07 16:25:51 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubstr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	if (start > s_len)
	{
		len = 0;
		start = s_len;
	}
	if (start + len > s_len)
		len = s_len - start;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memcpy(res, &s[start], len);
	return (res);
}
