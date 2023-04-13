/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:22 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/13 15:27:11 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*word_without_quotes(char *str, int i, int j)
{
	char	*new_word;
	int		k;

	new_word = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_word)
		return (NULL);
	k = -1;
	while (++k < j)
		new_word[k] = str[k];
	while (k < i)
	{
		new_word[k] = str[k + 1];
		k++;
	}
	while (str[k])
	{
		new_word[k] = str[k + 2];
		k++;
	}
	new_word[k] = '\0';
	free(str);
	return (new_word);
}

int	quotes_removal(t_data *data)
{
	t_lexer	*tmp;
	int		i;
	int		j;

	tmp = data->lexer;
	tmp->s_q = 0;
	tmp->d_q = 0;
	while (tmp != NULL)
	{
		if (tmp->word == NULL || ((ft_strchr(tmp->word, '\'') == NULL \
			&& ft_strchr(tmp->word, '"') == NULL)))
		{
			tmp = tmp->next;
			continue ;
		}
		i = 0;
		while (tmp->word[i])
		{
			if (tmp->word[i] == '\'')
				tmp->s_q = 1;
			if (tmp->word[i] == '"')
				tmp->d_q = 1;
			if (tmp->word[i] == '\'' || tmp->word[i] == '"')
				break ;
			i++;
		}
		j = i++;
		// i++;
		// while ((tmp->word[++i] != '\'' && tmp->s_q == 1) 
		// 		|| (tmp->word[++i] != '"' && tmp->d_q == 1))
		while ((tmp->word[i] != '"' && tmp->d_q == 1) \
				|| (tmp->word[i] != '\'' && tmp->s_q == 1))
			i++;
		tmp->word = word_without_quotes(tmp->word, i - 1, j);
		// if (!new_word)
		// 	;
		printf("quotes-> word :%s\n", tmp->word);
		tmp = tmp->next;
	}
	return (1);
}
