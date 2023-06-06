/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_join_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 08:35:29 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/06 08:36:46 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*join_all_mid(t_data *data, char *str, t_substr *s)
{
	free(s);
	str = NULL;
	if (s->before != NULL && s->middle != NULL)
		str = ft_strjoin_free(data, s->before, s->middle);
	else if (s->before == NULL && s->middle != NULL)
	{
		str = ft_strdup(s->middle);
		free(s->middle);
	}
	else if (s->before != NULL && s->middle == NULL)
	{
		str = ft_strdup(s->before);
		free(s->before);
	}
	if (s->after != NULL)
		str = ft_strjoin_free(data, s, s->after);
	if (!str)
		exit_error(data, "minishell: malloc error : ");
	return (str);
}

char	*join_all_sub(t_data *data, char *str, t_substr *s)
{
	free(str);
	str = NULL;
	if (s->sub_b != NULL && s->sub_m != NULL)
		str = ft_strjoin_free(data, s->sub_b, s->sub_m);
	else if (s->sub_b == NULL && s->sub_m != NULL)
	{
		str = ft_strdup(s->sub_m);
		free(s->sub_m);
	}
	else if (s->sub_b != NULL && s->sub_m == NULL)
	{
		str = ft_strdup(s->sub_b);
		free(s->sub_b);
	}
	if (s->sub_a != NULL)
		str = ft_strjoin_free(data, str, s->sub_a);
	if (!str)
		exit_error(data, "minishell: malloc error : ");
	return (str);
}
