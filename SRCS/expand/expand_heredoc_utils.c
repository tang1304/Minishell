/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:38:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 12:57:22 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	question_mark_hd(t_data *data, t_substr *s, size_t *i)
{
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	s->sub_m = ft_itoa(g_status);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	number_xpd_hd(t_data *data, t_substr *s, size_t *i)
{
	char	*buf;
	int		err;

	err = 0;
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	buf = ft_substr(s->s, ft_strlen(s->sub_b) + 1, *i);
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	s->sub_m = get_var(data, buf, &err);
	// if (err > 0)
	// 	;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}
