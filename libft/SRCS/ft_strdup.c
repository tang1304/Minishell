/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:07:35 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:32:00 by rrebois          ###   ########lyon.fr   */
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
