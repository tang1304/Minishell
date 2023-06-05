/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:33:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/31 10:33:04 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*str_without_single_quotes(char *str, int i, int j)
{
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!new_word)//
		return (NULL);
	while (i < j)
	{
		new_word[i] = str[i];
		i++;
	}
	new_word[i] = '\0';
	free(str);
	return (new_word);
}

char	*remove_str_middle_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	str = str_without_single_quotes(str, 0, i);
	return (str);
}

static char	*expand_number_mark(t_data *data, t_substr *s, size_t *j, char c)
{
	*j = *j + 1;
	if (*j > 1)
		s->sub_b = ft_substr(s->middle, 0, *j - 1);
	*j = *j + 1;
	if (c != '?')
	{
		s->sub_a = ft_substr(s->middle, *j, ft_strlen(s->middle) - *j);
		s->sub_m = get_var(data, s->sub_m, 0);
		*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
		s->middle = join_all(s->middle, s->sub_b, s->sub_m, s->sub_a);
	}
	else
	{
		s->sub_a = ft_substr(s->middle, *j, ft_strlen(s->middle) - *j);
		s->sub_m = ft_itoa(g_status);
		*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
		s->middle = join_all(s->middle, s->sub_b, s->sub_m, s->sub_a);
	}
	return (s->middle);
}

static char	*expand_str(t_data *data, t_substr *s)
{
	size_t	j;

	j = 0;
	while (s->middle[j] != '\0')
	{
		if (s->middle[j] == '$' && (ft_isalpha(s->middle[j + 1]) == 1))
		{
			j++;
			if (j > 0)
				s->sub_b = ft_substr(s->middle, 0, j - 1);
			while (ft_isalnum(s->middle[j]) == 1)
				j++;
			set_sub_strs(s, j);
			s->sub_m = get_var(data, s->sub_m, 0);
			j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
			s->middle = join_all(s->middle, s->sub_b, s->sub_m, s->sub_a);
		}
		else if (s->middle[j] == '$' && (s->middle[j + 1] == '?' || \
				ft_isdigit(s->middle[j + 1]) == 1))
			s->middle = expand_number_mark(data, s, &j, s->middle[j + 1]);
		else
			j++;
	}
	return (s->middle);
}

void	expand_quotes(t_data *data, t_substr *str, size_t *i, char c)
{
	size_t	j;

	j = *i + 1;
	if (*i > 0)
		str->before = ft_substr(str->s, 0, *i);
	*i = *i + 1;
	while (str->s[*i] != c)
		*i = *i + 1;
	str->middle = ft_substr(str->s, j, *i - j);
	if (*i + 1 < ft_strlen(str->s))
		str->after = ft_substr(str->s, *i + 1, ft_strlen(str->s));
	if (c == '"' && str->middle != NULL)
		str->middle = expand_str(data, str);
	else if (c == '\'' && str->middle != NULL)
		str->middle = remove_str_middle_quote(str->middle, c);
	*i = ft_strlen(str->before) + ft_strlen(str->middle);
	str->s = join_all(str->s, str->before, str->middle, str->after);
}
