/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate_char_matrix.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebartol <lebartol@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lebartol          #+#    #+#             */
/*   Updated: 2024/05/20 17:31:40 by lebartol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_duplicate_char_matrix(char **matrix)
{
	int		count_rows;
	int		str_len;
	char	**result;
	int		i;

	count_rows = ft_count_matrix_row((void **)matrix);
	result = malloc(sizeof(char *) * (count_rows + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		str_len = ft_strlen(matrix[i]);
		result[i] = ft_calloc(str_len + 1, sizeof(char));
		ft_strlcpy(result[i], matrix[i], str_len + 1);
		i++;
	}
	result[i] = NULL;
	return (result);
}
