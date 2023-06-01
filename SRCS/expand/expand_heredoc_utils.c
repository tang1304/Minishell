/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:38:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/01 07:54:08 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	question_mark_hd(t_substr *s, size_t *i)
{
	// char	*buf;

	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	// buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = ft_itoa(g_status);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

void	number_xpd_hd(t_data *data, t_substr *s, size_t *i)
{
	char	*buf;

	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
// printf("STRING BEFORE = %s\n", s->sub_b);
	buf = ft_substr(s->s, ft_strlen(s->sub_b) + 1, *i);
// printf("STRING expand = %s\n", s->sub_m);
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
// printf("STRING AFTER = %s\n", s->sub_a);
	// buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, buf);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}
