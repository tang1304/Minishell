/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/25 09:52:02 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_var(t_data *data, char *s)
{
	char	*var;
	size_t	i;
	size_t	k;

	k = 0;
	var = ft_strdup("");
	// if (var == NULL)
	// 	return (NULL);
	while (data->envp[k])
	{
		i = 0;
		while (data->envp[k][i] != '=')
			i++;
		if (ft_strncmp(data->envp[k], s, i - 1) == 0)
		{
			free(var);
			var = ft_substr(data->envp[k], i + 1, (ft_strlen(*data->envp)));
			// if (var == NULL)
			// 	return (NULL);
			break ;
		}
		k++;
	}
	return (var);
}

char	*join_all(char *s, char *b, char *e, char *a)
{
	free(s);
	s = NULL;
	if (b != NULL && e != NULL)
		s = ft_strjoin_free(b, e);
	else if (b == NULL && e != NULL)
		s = e;
	else if (b != NULL && e == NULL)
		s = b;
	if (a != NULL)
		s = ft_strjoin_free(s, a);
	return (s);
}
