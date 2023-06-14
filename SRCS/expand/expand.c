/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/14 13:53:51 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

static void	expand_dollar(t_data *data, t_substr *s, size_t *i, size_t index)
{
	int		err;

	err = 0;
	if (!check_nbr_question(data, s, i, index))
		return ;
	substrs_prep(data, s, i);
	data->buf = ft_substr_check(s->s, ft_strlen(s->sub_b), *i - \
							(ft_strlen(s->sub_b)), &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error");
	s->sub_m = get_var(data, data->buf, &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error");
	if (check_space_expand(data, s, index) == 1)
		return ;
	if (check_space_expand(data, s, index) == 2)
	{
		free(s->sub_m);
		s->sub_m = malloc(sizeof(char *) * 1);
		s->sub_m[0] = '\0';
	}
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

// static char	*check_char(t_data *data, char *s, size_t *i, size_t index)
// {
// 	t_substr	str;

// 	ft_bzero(&str, sizeof(t_substr));
// 	str.s = s;
// 	if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != ' ')
// 		expand_dollar(data, &str, i, index);
// 	else if (s[*i] == '\'')
// 		expand_quotes(data, &str, i, '\'');
// 	else if (s[*i] == '"')
// 		expand_quotes(data, &str, i, '"');
// 	else
// 		*i = *i + 1;
// 	if (str.s == NULL)
// 	{
// 		str.s = malloc(sizeof(char *) * 1);
// 		str.s[0] = '\0';
// 	}
// 	return (str.s);
// }

static void	check_char(t_data *data, t_lexer *l, size_t *i)
{
	t_substr	str;

	while (l->word[*i])
	{
		ft_bzero(&str, sizeof(t_substr));
		str.s = l->word;
		if (l->word[*i] == '$' && l->word[*i + 1] && l->word[*i + 1] != ' ')
			expand_dollar(data, &str, i, l->index);
		else if (l->word[*i] == '\'')
			expand_quotes(data, &str, i, '\'');
		else if (l->word[*i] == '"')
			expand_quotes(data, &str, i, '"');
		else
			*i = *i + 1;
		if (str.s == NULL)
		{
			str.s = malloc(sizeof(char *) * 1);
			str.s[0] = '\0';
		}
		l->word = str.s;
		if (!l->word)
			l = data->lexer;
	}
}

static int	check_word(t_data *data, size_t index)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	if ((ft_strncmp(tmp->word, "\"\"", 2) == 0 || ft_strncmp(tmp->word, \
		"\'\'", 2) == 0) && (ft_strlen(tmp->word) == 2 && !tmp->prev))
		return (100);
	else if ((ft_strncmp(tmp->word, "\"\"", 2) == 0 || ft_strncmp(tmp->word, \
	"\'\'", 2) == 0) && ft_strlen(tmp->word) == 2 && tmp->prev && \
	ft_strncmp(tmp->prev->word, "echo", 4) != 0)
	{
		free(tmp->word);
		tmp->word = malloc(sizeof(char *) * 2);
		tmp->word[0] = ' ';
		tmp->word[1] = '\0';
		return (101);
	}
	return (0);
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
			if (check_word(data, tmp->index) != SUCCESS)
			{
				tmp = tmp->next;
				continue ;
			}
			check_char(data, tmp, &i);
			// while (tmp->word[i] != '\0')
			// {
			// 	tmp->word = check_char(data, tmp->word, &i, tmp->index);
			// 	if (!tmp->word)
			// 		tmp = data->lexer;
			// }
			if (tmp->index != data->svd_index)
				tmp = update_tmp_index(data, &i);
		}
		tmp = tmp->next;
		data->svd_index++;
	}
	remove_nodes(data);
}
