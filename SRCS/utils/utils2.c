/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 15:44:44 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	return (free(s1), free(s2), ptr);
}

void	complete_out_data(t_data *data, t_lexer *tmp, char *file, int valid)
{
	if (tmp->outfile != NULL)
	{
		free(tmp->outfile);
		tmp->outfile = NULL;
	}
	tmp->fdout = data->fdout;
	if (valid == 0)
	{
		tmp->outfile = ft_strdup(file);
		if (!tmp->outfile)
			exit_error(data, "minishell: malloc error 25: ");
		return ;
	}
	else
	{
		tmp->out_err = 1;
		return ;
	}
}

size_t	ft_strlen_pp(char **s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_substr_check(char *s, size_t start, size_t len, int *err)
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
		return (*err = 1, NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = *(char *)(s + start + i);
		i++;
	}
	ptr[i] = '\0';
	if (ptr[0] == '\0')
		return (free(ptr), NULL);
	return (ptr);
}
