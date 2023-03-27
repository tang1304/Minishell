/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:43:40 by rrebois           #+#    #+#             */
/*   Updated: 2023/02/24 13:11:52 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	leneedle;

	i = 0;
	leneedle = ft_strlen(needle);
	if (leneedle == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len && \
		haystack[i + j] != '\0')
		{
			j++;
			if (j == leneedle)
			{
				haystack = &haystack[i];
				return ((char *)haystack);
			}
		}
		i++;
	}
	return (NULL);
}
