/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:27:55 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/20 10:05:52 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static char	**ft_free(char **ptr, size_t j)
{
	size_t	x;

	x = 0;
	while (x < j)
	{
		free(ptr[x]);
		x++;
	}
	free(ptr);
	return (NULL);
}

static char	**ft_cut(char const *s, char c, char **ptr, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (j < count)
		{
			ptr[j] = ft_substr(s, start, i - start);
			if (ptr[j] == NULL)
				return (ft_free(ptr, j));
			j++;
		}
	}
	ptr[j] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**ptr;

	i = 0;
	count = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	ptr = (char **)malloc(sizeof(*ptr) * (count + 1));
	if (ptr == NULL)
		return (NULL);
	ptr = ft_cut(s, c, ptr, count);
	return (ptr);
}
