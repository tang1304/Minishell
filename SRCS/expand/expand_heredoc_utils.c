/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:38:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 08:43:51 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	question_mark_hd(t_data *data, t_substr *s, size_t *i, char *buffer)
{
	int	err;

	err = 0;
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, &err);
		if (err > 0)
			expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr_check(s->s, *i + 1, ft_strlen(s->s) - *i, &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	s->sub_m = ft_itoa(g_status);
	if (s->sub_m == NULL)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	number_xpd_hd(t_data *data, t_substr *s, size_t *i, char *buffer)
{
	int		err;

	err = 0;
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, &err);
		if (err > 0)
			expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	}
	data->buf = ft_substr_check(s->s, ft_strlen(s->sub_b) + 1, *i, &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	s->sub_a = ft_substr_check(s->s, *i + 1, ft_strlen(s->s) - *i, &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	s->sub_m = get_var(data, buf, &err);
	if (err > 0)
		expand_error_hd(data, s, buffer, "minishell: malloc_error: ");
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}
