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

void	expand_dollar_hd(t_data *data, t_substr *s, size_t *i, char *buffer)
{
	*i = *i + 1;
	if (s->s[*i] == '?')
	{
		question_mark_hd(data, s, i, buffer);
		return ;
	}
	else if (ft_isdigit(s->s[*i]) == 1)
	{
		number_xpd_hd(data, s, i, buffer);
		return ;
	}
	else
		string_xpd_hd(data, s, i, buffer);
}

char	*expand_line(t_data *data, char *str, char *buffer)
{
	size_t		i;
	t_substr	ptr;

	i = 0;
	ft_bzero(&ptr, sizeof(t_substr));
	ptr.s = ft_strjoin(str, "\n");
	if (!ptr.s)
	{
		free(buffer);
		exit_error(data, "minishell: malloc error");
	}
	if (data->hd->xpd[data->hd->heredoc] == 1)
		return (ptr.s);
	while (ptr.s[i] != '\0')
	{
		if (ptr.s[i] == '$' && ptr.s[i + 1] && ptr.s[i + 1] != ' ')
			expand_dollar_hd(data, &ptr, &i, buffer);
		else
			i++;
	}
	return (ptr.s);
}

static void	set_data_xpd(t_data *data)
{
	data->hd->xpd = (int *)malloc(sizeof(int) * data->hd->hd_count);
	if (data->hd->xpd == NULL)
		exit_error(data, "minishell: malloc error 1");
}

void	prepare_expand_hd(t_data *data)
{
	int		i;
	size_t	j;
	int		quote;

	if (data->hd->hd_count > 0)
		set_data_xpd(data);
	i = 0;
	while (data->hd->limiter[i] != 0)
	{
		j = 0;
		quote = 0;
		data->hd->xpd[i] = 0;
		while (data->hd->limiter[i][j] != '\0')
		{
			if (data->hd->limiter[i][j] == '\'' || \
			data->hd->limiter[i][j] == '"')
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
	while (data->hd->limiter[i] != 0)
	{
		data->hd->limiter[i] = str_quotes_removal(data, data->hd->limiter[i]);
		i++;
	}
}
