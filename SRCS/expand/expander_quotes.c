/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:22 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 16:06:44 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	set_sub_strs(t_data *data, t_substr *s, size_t j, int *err)
{
	s->sub_a = ft_substr_check(s->middle, j, ft_strlen(s->middle) - j, err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
	data->buf = ft_substr_check(s->middle, ft_strlen(s->sub_b), \
	j - (ft_strlen(s->sub_b)), err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
	s->sub_m = get_var(data, data->buf, err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
}

static char	*word_without_quotes(t_data *data, char *str, int i, int j)
{
	char	*new_word;
	int		k;

	new_word = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_word)
		exit_error(data, "minishell: malloc error 15: ");
	k = -1;
	while (++k < i)
		new_word[k] = str[k];
	while (++k < j)
		new_word[k - 1] = str[k];
	k++;
	while ((size_t)k < ft_strlen(str))
	{
		new_word[k - 2] = str[k];
		k++;
	}
	new_word[k - 2] = '\0';
	free(str);
	return (new_word);
}

static int	quote_starting_point(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			break ;
		i++;
	}
	return (i);
}

static int	quote_pairs(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1]) || (str[i] == '"' && str[i + 1]))
		{
			j++;
			i += quote_handling(str, i, str[i]) + 1;
		}
		else
			i++;
	}
	return (j);
}

char	*str_quotes_removal(t_data *data, char *str)
{
	int	i;
	int	j;
	int	k;
	int	q_pairs;

	q_pairs = quote_pairs(str);
	k = -1;
	i = 0;
	while (++k < q_pairs)
	{
		i = quote_starting_point(str, i);
		j = i + 1;
		while (str[j] != str[i] && str[j] != '\0')
			j++;
		str = word_without_quotes(data, str, i, j);
	}
	return (str);
}
