/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:07:35 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 14:38:11 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(*ptr) * (len + 1));
	if (ptr == NULL)
		return (ptr);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
