/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnmltcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 22:58:45 by zmoumen           #+#    #+#             */
/*   Updated: 2023/07/29 17:34:49 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief compare with mutliple strings, return index of matched string
/// @param str buffer to be checked
/// @param mltcmp the group of strings to be compared against
/// @param deli the delimiter between the strings in mltcmp
/// @param len length of the buffer to be checked
/// @return	the index of the matched string, -1 if no match found
int	ft_strnmltcmp(char	*str, char	*mltcmp, char deli, size_t len)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = ft_split(mltcmp, deli);
	while (splitted[i])
	{
		if (ft_strncmp(str, splitted[i], len) == 0)
		{
			ft_strlstfree(splitted);
			return (i);
		}
		i++;
	}
	ft_strlstfree(splitted);
	return (-1);
}
