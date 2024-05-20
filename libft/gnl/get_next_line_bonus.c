/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/04/29 12:26:39 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

//massimo numero di file che possono essere gestiti
# ifndef OPEN_MAX
#  define OPEN_MAX 2048
# endif

int		ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		has_nl(char const *str);

char	*null_init(void)
{
	char	*res;

	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	*res = 0;
	return (res);
}

char	*ft_substr_gnl(char *str, unsigned int start, size_t size)
{
	size_t	len;
	char	*sub;

	len = ft_strlen_gnl(str);
	if (start >= len)
		return (null_init());
	if (len - start < size)
		size = len - start;
	sub = malloc (sizeof(char) * (size + 1));
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--)
		sub[size] = str[start + size];
	return (sub);
}

char	*split_by_nl(char **temp)
{
	char	*line;
	char	*cpy;
	int		i;
	int		len;

	i = 0;
	len = 0;
	cpy = *temp;
	while (cpy[len] && cpy[len] != '\n')
		++len;
	len += (cpy[len] == '\n');
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (free(*temp), NULL);
	line[len] = 0;
	while (i < len)
	{
		line[i] = cpy[i];
		i++;
	}
	cpy = ft_substr_gnl(cpy, len, ft_strlen_gnl(cpy));
	free(*temp);
	*temp = cpy;
	return (line);
}

char	*ft_read(char *temp, int fd)
{
	ssize_t		r;
	char		*buf;

	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free (temp), NULL);
	r = 1;
	while (r && has_nl(temp) == -1)
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (free (buf), free (temp), NULL);
		buf[r] = '\0';
		temp = ft_strjoin_gnl(temp, buf);
		if (!temp)
			return (free (buf), NULL);
	}
	return (free (buf), temp);
}

char	*get_next_line(int fd, t_bool last_call)
{
	static char	*temp[OPEN_MAX];

	if (last_call)
	{
		free(temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = null_init();
	if (!temp[fd])
		return (NULL);
	temp[fd] = ft_read (temp[fd], fd);
	if (!temp[fd])
		return (NULL);
	if (!*temp[fd])
	{
		free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (split_by_nl(&temp[fd]));
}

// int main (int argc, char **argv)
// {
// 	int fd;
// 	int fd2;
// 	int fd3;
// 	char *c;

// 	fd = argc;

// 	fd = open(argv[1], O_RDONLY);
// 	fd2 = open(argv[2], O_RDONLY);
// 	fd3 = open(argv[3], O_RDONLY);
// 	c = "ciao";
// 	while (c)
// 	{
// 		c = get_next_line(fd);
// 		printf("%s\n", c);
// 		c = get_next_line(fd2);
// 		printf("%s\n", c);
// 		c = get_next_line(fd3);
// 		printf("%s\n", c);
// 		free(c);
// 	}
// }
