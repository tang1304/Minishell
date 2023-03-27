/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:54:41 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:32:22 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		count;
	size_t		count2;
	size_t		i;

	count = 0;
	count2 = 0;
	i = 0;
	if (dst == NULL && dstsize == 0)
		return (0);
	while (dst[count] != '\0' && count < dstsize)
		count++;
	while (src[count2] != '\0')
		count2++;
	while (src[i] != '\0' && dstsize && (count + i) < (dstsize - 1))
	{
		dst[count + i] = src[i];
		i++;
	}
	if (count < dstsize)
		dst[count + i] = 0;
	return (count + count2);
}
