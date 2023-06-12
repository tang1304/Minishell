/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 08:53:02 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 08:53:18 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	expand_quotes(t_data *data, t_substr *str, size_t *i, char c)
{
	size_t	j;
	int		err;

	err = 0;
	j = *i + 1;
	if (*i > 0)
		str->before = ft_substr_check(str->s, 0, *i, &err);
	if (err > 0)
		expand_error(data, str, "minishell: malloc_error: ");
	*i = *i + 1;
	while (str->s[*i] != c)
		*i = *i + 1;
	str->middle = ft_substr_check(str->s, j, *i - j, &err);
	if (err > 0)
		expand_error(data, str, "minishell: malloc_error: ");
	if (*i + 1 < ft_strlen(str->s))
		str->after = ft_substr_check(str->s, *i + 1, ft_strlen(str->s), &err);
	if (err > 0)
		expand_error(data, str, "minishell: malloc_error: ");
	if (c == '"' && str->middle != NULL)
		str->middle = expand_str(data, str, &err);
	else if (c == '\'' && str->middle != NULL)
		str->middle = remove_str_middle_quote(data, str->middle, c);
	*i = ft_strlen(str->before) + ft_strlen(str->middle);
	str->s = join_all_mid(data, str->s, str);
}
