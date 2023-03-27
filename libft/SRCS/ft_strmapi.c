/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:53:17 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:32:32 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	ptr = ft_strdup(s);
	if (ptr == NULL)
		return (NULL);
	while (ptr[i] != '\0')
	{
		ptr[i] = f(i, ptr[i]);
		i++;
	}
	return (ptr);
}
