/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:38:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/06 08:40:17 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	question_mark_hd(t_data *data, t_substr *s, size_t *i)
{
	if (*i > 1)
	{
		s->sub_b = ft_substr(s->s, 0, *i - 1);
		if (!s->sub_b)
			exit_error(data, "minishell: malloc error: ");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	if (!s->sub_a)
		exit_error(data, "minishell: malloc error: ");
	s->sub_m = ft_itoa(g_status);
	if (!s->sub_m)
		exit_error(data, "minishell: malloc error: ");
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	number_xpd_hd(t_data *data, t_substr *s, size_t *i)
{
	char	*buf;

	if (*i > 1)
	{
		s->sub_b = ft_substr(s->s, 0, *i - 1);
		if (!s->sub_b)
			exit_error(data, "minishell: malloc error: ");
	}
	buf = ft_substr(s->s, ft_strlen(s->sub_b) + 1, *i);
	if (!buf)
		exit_error(data, "minishell: malloc error: ");
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	if (!s->sub_a)
		exit_error(data, "minishell: malloc error: ");
	s->sub_m = get_var(data, buf, 0);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}
