/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 15:00:18 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*check_char(t_data *data, char *s, size_t *i, size_t index)
{
	t_substr	str;

	ft_bzero(&str, sizeof(t_substr));
	str.s = s;
	if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != ' ')
		expand_dollar(data, &str, i, index);
	else if (s[*i] == '\'')
		expand_quotes(data, &str, i, '\'');
	else if (s[*i] == '"')
		expand_quotes(data, &str, i, '"');
	else
		*i = *i + 1;
	return (str.s);
}

static void	remove_nodes(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->rm == 1)
		{
			remove_single_node(data, tmp->index);
			tmp = data->lexer;
			continue ;
		}
		tmp = tmp->next;
	}
	add_index(data);
}

static int	check_nbr_question(t_data *data, t_substr *s, size_t *i, \
								size_t index)
{
	*i = *i + 1;
	if (s->s[*i] == '?')
	{
		question_mark(data, s, i, index);
		return (0);
	}
	else if (ft_isdigit(s->s[*i]) == 1)
	{
		number_xpd(data, s, i, index);
		return (0);
	}
	return (1);
}

static void	substrs_prep(t_data *data, t_substr *s, size_t *i)
{
	int	err;

	err = 0;
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, &err);
		if (err > 0)
			expand_error(data, s, "minishell: malloc_error1");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr_check(s->s, *i, ft_strlen(s->s) - *i + 1, &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error2");
}

void	expand_dollar(t_data *data, t_substr *s, size_t *i, size_t index)
{
	char	*buf;
	int		err;

	err = 0;
	if (!check_nbr_question(data, s, i, index))
		return ;
	substrs_prep(data, s, i);
	buf = ft_substr_check(s->s, ft_strlen(s->sub_b), *i - \
							(ft_strlen(s->sub_b)), &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error");
	s->sub_m = get_var(data, buf, &err);
	if (err > 0)
	{
		free(buf);
		expand_error(data, s, "minishell: malloc error");
	}
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	expand(t_data *data)
{
	size_t	i;
	t_lexer	*tmp;

	data->svd_index = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->word != NULL)
		{
			while (tmp->word[i] != '\0')
			{
				tmp->word = check_char(data, tmp->word, &i, tmp->index);
				if (!tmp->word)
					tmp = data->lexer;
			}
			if (tmp->index != data->svd_index)
				tmp = update_tmp_index(data, &i);
		}
		tmp = tmp->next;
		data->svd_index++;
	}
	remove_nodes(data);
}
