/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/06 14:41:50 by rrebois          ###   ########lyon.fr   */
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
