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

char	*str_without_single_quotes(t_data *data, char *str, int i, int j)
{
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!new_word)
		exit_error(data, "minishell: dup error: ");
	while (i < j)
	{
		new_word[i] = str[i];
		i++;
	}
	new_word[i] = '\0';
	free(str);
	return (new_word);
}

char	*remove_str_middle_quote(t_data *data, char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	str = str_without_single_quotes(data, str, 0, i);
	return (str);
}

static char	*expand_number_mark(t_data *data, t_substr *s, size_t *j, char c)
{
	*j = *j + 1;
	if (*j > 1)
	{
		s->sub_b = ft_substr(s->middle, 0, *j - 1);
		if (!s->sub_b)
			exit_error(data, "minishell: malloc error: ");
	}
	*j = *j + 1;
	if (c != '?')
	{
		s->sub_a = ft_substr(s->middle, *j, ft_strlen(s->middle) - *j);
		s->sub_m = get_var(data, s->sub_m, 0);
		*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
		s->middle = join_all(data, s->middle, s);
	}
	else
	{
		s->sub_a = ft_substr(s->middle, *j, ft_strlen(s->middle) - *j);
		s->sub_m = ft_itoa(g_status);
		*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
		s->middle = join_all(data, s->middle, s);
	}
	if (!s->sub_a || !s->sub_m)
		exit_error(data, "minishell: malloc error: ");
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
				s->sub_b = substr_check(data, s->middle, 0, j - 1);
			while (ft_isalnum(s->middle[j]) == 1)
				j++;
			set_sub_strs(data, s, j);
			s->sub_m = get_var(data, s->sub_m, 0);
			j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
			s->middle = join_all(data, s->middle, s);
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
		str->before = substr_check(data, str->s, 0, *i);
	*i = *i + 1;
	while (str->s[*i] != c)
		*i = *i + 1;
	str->middle = ft_substr(str->s, j, *i - j);
	if (!str->middle)
		exit_error(data, "minishell: malloc error: ");
	if (*i + 1 < ft_strlen(str->s))
	{
		str->after = ft_substr(str->s, *i + 1, ft_strlen(str->s));
		if (!str->after)
			exit_error(data, "minishell: malloc error: ");
	}
	if (c == '"' && str->middle != NULL)
		str->middle = expand_str(data, str);
	else if (c == '\'' && str->middle != NULL)
		str->middle = remove_str_middle_quote(data, str->middle, c);
	if (!str->middle)
		exit_error(data, "minishell: malloc error: ");
	*i = ft_strlen(str->before) + ft_strlen(str->middle);
	str->s = join_all(data, str->s, str);
}
