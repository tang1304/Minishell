/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:24 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 14:32:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	string_xpd_hd(t_data *data, t_substr *s, size_t *i, char *buffer)
{
	int		err;

	err = 0;
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, &err);
		if (err > 0)
			expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr_check(s->s, *i, ft_strlen(s->s) - *i, &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	data->buf = ft_substr_check(s->s, ft_strlen(s->sub_b), \
	*i - (ft_strlen(s->sub_b)), &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	s->sub_m = get_var(data, data->buf, &err);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	string_xpd(t_data *data, t_substr *s, size_t *i, size_t index)
{
	int	err;

	err = 0;
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i + 1);
	data->buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, data->buf, &err);
	// if (err > 0)
	// 	;
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}
