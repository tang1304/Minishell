/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:29:47 by rrebois           #+#    #+#             */
/*   Updated: 2022/12/19 11:32:49 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static size_t	index_front(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		check;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		check = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				check = 1;
			j++;
		}
		if (check == 0)
			break ;
		i++;
	}
	return (i);
}

static size_t	index_back(char const *s1, char const *set, size_t start)
{
	size_t	i;
	size_t	j;
	int		check;

	i = ft_strlen(s1);
	while (i - 1 > start)
	{
		j = 0;
		check = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[i - 1])
				check = 1;
			j++;
		}
		if (check == 0)
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	start = index_front(s1, set);
	end = index_back(s1, set, start);
	ptr = (char *)malloc(sizeof(*ptr) * ((end - start) + 1));
	if (ptr == NULL)
		return (NULL);
	while (start + i < end)
	{
		ptr[i] = ((char *)s1)[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
