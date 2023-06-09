/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:50:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 08:21:41 by rrebois          ###   ########lyon.fr   */
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

char	*substr_check(t_data *data, char *s, size_t i, size_t len)
{
	char	*str;

	(void)data;
	str = ft_substr(s, i, len);
	return (str);
}
