/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FunzioniDaSostituireConLibft.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:44:58 by maceccar          #+#    #+#             */
/*   Updated: 2023/12/11 18:30:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	i = 0;
	if (size)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

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

void	*ft_bzero(void *dest, size_t count)
{
	return (ft_memset(dest, '\0', count));
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*tmp;

	tmp = malloc(nitems * size);
	if (!tmp)
		return (NULL);
	return (ft_bzero(tmp, nitems * size));
}

static size_t	ft_count_arr(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	in_arr;

	i = 0;
	count = 0;
	in_arr = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_arr == 0)
		{
			count++;
			in_arr = 1;
		}
		else if (s[i] == c)
			in_arr = 0;
		i++;
	}
	return (count);
}

static char	*ft_make_string(char const *s, size_t start, char c)
{
	char	*division;
	size_t	i;
	size_t	j;
	size_t	str_len;

	i = 0;
	j = start;
	str_len = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	while (s[j] != c && s[j])
	{
		j++;
		str_len++;
	}
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	while (i < str_len)
		division[i++] = s[start++];
	division[i] = '\0';
	return (division);
}

static void	ft_clear(char **array, size_t arr_index)
{
	while (arr_index-- > 0)
		free(array[arr_index]);
	free(array);
}

static char	**ft_make_split(char **array, char const *s, char c)
{
	int	i;
	int	in_arr;
	int	arr_index;

	i = -1;
	in_arr = 0;
	arr_index = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && in_arr == 0)
		{
			array[arr_index++] = ft_make_string(s, i, c);
			if (array[arr_index - 1] == NULL)
			{
				ft_clear(array, arr_index);
				return (NULL);
			}
			in_arr = 1;
		}
		else if (s[i] == c)
			in_arr = 0;
	}
	array[arr_index] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_count_arr(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_make_split(array, s, c);
	if (array == NULL)
		return (NULL);
	else
		return (array);
}


