/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 15:51:17 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
			exit_error(data, "minishell: malloc error");
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
