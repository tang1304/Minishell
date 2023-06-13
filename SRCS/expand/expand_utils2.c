/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:40:52 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/19 14:40:52 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_lexer	*update_tmp_index(t_data *data, size_t *i)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != data->svd_index)
		tmp = tmp->next;
	if (tmp->word != NULL)
		*i = ft_strlen(tmp->word);
	else
		*i = ft_strlen(tmp->token);
	return (tmp);
}

static int	check_only_space(char *str)
{
	size_t	space;
	size_t	i;

	space = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			space++;
		i++;
	}
	if (i == space)
		return (1);
	return (0);
}

int	check_space_expand(t_data *data, t_substr *s, size_t index)
{
	size_t	j;
	int		split;

	j = 0;
	split = 0;
	if (check_only_space(s->sub_m))
		return (2);
	while (s->sub_m[j] != '\0')
	{
		if (s->sub_m[j] == ' ')
			split = 1;
		j++;
	}
	if (split == 1)
	{
		modify_lxr_nds(data, s, index);
		free(s->sub_m);
		return (1);
	}
	return (0);
}

// if (!*delimiter)

void	substrs_prep(t_data *data, t_substr *s, size_t *i)
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
