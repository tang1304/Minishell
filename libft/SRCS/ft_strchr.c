/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:52:35 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:31:56 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if (c == 0 || ptr[i] == (char)c)
		return (&ptr[i]);
	return (NULL);
}
