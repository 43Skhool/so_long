/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:33:46 by lebartol          #+#    #+#             */
/*   Updated: 2023/11/19 23:41:35 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

static int	newline_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

static char	*addtostash(char *stash, char *content)
{
	if (!content)
		return (stash);
	if (!stash)
		return (content);
	stash = ft_strjoin(stash, content);
	return (stash);
}

static char	*get_line(char *stash, int fd)
{
	static char	*remainder;
	char		*res;
	int			cursor;
	char		*buffer;

	if (remainder)
	{
		stash = ft_substr(remainder, 0, ft_strlen(remainder));
	}
	free(remainder);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	cursor = read(fd, buffer, BUFFER_SIZE);
	if (cursor > 0)
	{
		stash = addtostash(stash, buffer);
		return (get_line(stash, fd));
	}
	free(buffer);
	cursor = newline_check(stash);
	if (cursor != -1)
	{
		remainder = ft_substr(stash, cursor + 1, ft_strlen(stash));
		res = ft_substr(stash, 0, cursor + 1);
		free(stash);
		return (res);
	}
	free(stash);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*stash;

	stash = malloc(sizeof(char));
	if (fd < 0 || BUFFER_SIZE < 1 || !stash)
		return (NULL);
	return (get_line(stash, fd));
}
