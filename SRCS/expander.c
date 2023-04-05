/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/05 16:22:34 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	dollar_handle(t_data *data, char *str, int i)
{
	int	j;

	j = 1;
	while (ft_isalnum(str[i + j]))
	{
		j++;
	}
}

static int	dollar_in_quotes(t_data *data, char *str, int i)
{
	int	j;

	;
}

int	expand(t_data *data)
{
	int		i;
	t_lexer	*tmp;

	i = -1;
	tmp = data->lexer;
	while (tmp->next != NULL)
	{
		if (tmp->word == NULL)
			tmp = tmp->next;
		while (tmp->word[++i])
		{
			if (tmp->word[i] == '\'')
				i = i + dollar_in_quotes(data, tmp->word, i);
			else if (tmp->word[i] == '"')
				i = i + dollar_in_d_quotes(data, tmp->word, i);
			else if (tmp->word[i] == '$' && ft_isalnum(tmp->word[i + 1]))
				i = i + dollar_handle(data, tmp->word, i);
		}
	}
}
