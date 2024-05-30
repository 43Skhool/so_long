/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/20 17:31:40 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*result;
	size_t		j;
	size_t		str_len;

	str_len = ft_strlen(s);
	j = 0;
	if (start >= str_len)
	{
		result = ft_calloc(1, sizeof(char));
		return (result);
	}
	if (len > str_len)
		len = str_len;
	if (start + len > str_len)
		len = str_len - start;
	result = malloc(sizeof(char) * (len + 1));
	if (!result || !s)
		return (NULL);
	while ((start < str_len) && s[start + j] && j < len)
	{
		result[j] = s[start + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}
