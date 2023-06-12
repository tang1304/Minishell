/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:19:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 08:56:05 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	free_strs(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
}

char	*ft_strjoin_free_s2(t_data *data, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		exit_error(data, "minishell: malloc error: ");
	while (s1[i] != '\0')
	{
		ptr[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (free_strs(NULL, s2), ptr);
}

char	*ft_strjoin_expand(t_data *data, char *s1, char *s2)
{
	char	*ptr;

	if ((s1 == NULL || ft_strlen(s1) == 0) && s2 != NULL)
		return (s2);
	else if ((s2 == NULL || ft_strlen(s2) == 0) && s1 != NULL)
		return (s1);
	else if ((s2 == NULL && s1 == NULL) || \
	(ft_strlen(s1) == 0 || ft_strlen(s1) == 0))
		return (NULL);
	else
		ptr = ft_strjoin_free(data, s1, s2);
	return (ptr);
}

char	*ft_strjoin_free(t_data *data, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		exit_error(data, "minishell: malloc error 26: ");
	while (s1[i] != '\0')
	{
		ptr[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (free_strs(s1, s2), ptr);
}
