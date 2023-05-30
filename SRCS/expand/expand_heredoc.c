/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:16:39 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/24 08:16:39 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	expand_dollar_hd(t_data *data, t_substr *s, size_t *i)
{
	char	*buf;

	*i = *i + 1;
	if (s->s[*i] == '?')
	{
		question_mark_hd(s, i);
		return ; //add function with signals later
	}
	else if (ft_isdigit(s->s[*i]) == 1)
	{
		number_xpd_hd(data, s, i);
		return;
	}
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i);
	buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, buf);
printf("EXPAND WORD IS NOW = %s\n", s->sub_m);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

char	*expand_line(t_data *data, char *str)
{
	size_t		i;
	t_substr	ptr;

	i = 0;
	ft_bzero(&ptr, sizeof(t_substr));
	ptr.s = ft_strjoin(str, "\n");
	if (data->hd->xpd[data->hd->heredoc] == 1)
		return (ptr.s);
	while (ptr.s[i] != '\0')
	{
		if (ptr.s[i] == '$' && ptr.s[i + 1] && ptr.s[i + 1] != ' ')
			expand_dollar_hd(data, &ptr, &i);
		else
			i++;
	}
	return (ptr.s);
}

void	prepare_expand_hd(t_data *data)
{
	int		i;
	size_t	j;
	int		quote;

	data->hd->xpd = (int *)malloc(sizeof(int) * data->hd->hd_count);
	if (data->hd->xpd == NULL)
		return ;//garbage val?
	i = 0;
	while (data->hd->LIMITER[i] != 0)
	{
		j = 0;
		quote = 0;
		data->hd->xpd[i] = 0;
		while (data->hd->LIMITER[i][j] != '\0')
		{
			if (data->hd->LIMITER[i][j] == '\'' || \
			data->hd->LIMITER[i][j] == '"')
				quote = 1;
			j++;
		}
		if (quote == 1)
			data->hd->xpd[i] = 1;
		i++;
	}
	remove_limiter_quotes(data);
}

void	remove_limiter_quotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->hd->LIMITER[i] != 0)
	{
		data->hd->LIMITER[i] = str_quotes_removal(data->hd->LIMITER[i]);
		i++;
	}
}
