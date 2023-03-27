/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:23:43 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:32:53 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *)malloc(sizeof(*ptr) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = *(char *)(s + start + i);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
