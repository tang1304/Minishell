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
		exit_error(data, "minishell: dup error 16: ");
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
	if (!str)
		exit_error(data, "minishell: dup error 16: ");
	return (str);
}

static void	expand_quotes_question(t_data *data, t_substr *s, size_t *j, \
									int *err)
{
	s->sub_a = ft_substr_check(s->middle, *j, \
	ft_strlen(s->middle) - *j, err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
	s->sub_m = ft_itoa(g_status);
	*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->middle = join_all_sub(data, s->middle, s);
}

static char	*expand_number_mark(t_data *data, t_substr *s, size_t *j, char c)
{
	int	err;

	err = 0;
	*j = *j + 1;
	if (*j > 1)
		s->sub_b = ft_substr_check(s->middle, 0, *j - 1, &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
	*j = *j + 1;
	if (c != '?')
	{
		s->sub_a = ft_substr_check(s->middle, *j, \
		ft_strlen(s->middle) - *j, &err);
		if (err > 0)
			expand_error(data, s, "minishell: malloc_error: ");
		s->sub_m = get_var(data, s->sub_m, &err);
		if (err > 0)
			expand_error(data, s, "minishell: malloc_error: ");
		*j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
		s->middle = join_all_sub(data, s->middle, s);
	}
	else
		expand_quotes_question(data, s, j, &err);
	return (s->middle);
}

char	*expand_str(t_data *data, t_substr *s, int *err)
{
	size_t	j;

	j = 0;
	while (s->middle[j] != '\0')
	{
		if (s->middle[j] == '$' && (ft_isalpha(s->middle[j + 1]) == 1))
		{
			j++;
			if (j > 0)
				s->sub_b = ft_substr_check(s->middle, 0, j - 1, err);
			if (*err > 0)
				expand_error(data, s, "minishell: malloc_error: ");
			while (ft_isalnum(s->middle[j]) == 1)
				j++;
			set_sub_strs(data, s, j, err);
			j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
			s->middle = join_all_sub(data, s->middle, s);
		}
		else if (s->middle[j] == '$' && (s->middle[j + 1] == '?' || \
				ft_isdigit(s->middle[j + 1]) == 1))
			s->middle = expand_number_mark(data, s, &j, s->middle[j + 1]);
		else
			j++;
	}
	return (s->middle);
}
