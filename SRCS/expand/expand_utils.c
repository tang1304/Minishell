/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
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

static void	add_buf_lxr_tail(t_data *data, t_substr *s, t_lexer *buf, \
							char **ptr)
{
	t_lexer	*tmp;
	size_t	j;

	j = 1;
	while (ptr[j] != 0)
	{
		add_node(data, &data->lexer, ptr[j], 0);
		j++;
	}
	if (ft_strlen(s->sub_a) > 0)
		add_node(data, &data->lexer, s->sub_a, 0);
	tmp = data->lexer;
	add_index(data);
	while (tmp->next != NULL)
		tmp = tmp->next;
	data->svd_index = tmp->index;
	if (buf != NULL)
	{
		tmp->next = buf;
		buf->prev = tmp;
	}
	add_index(data);
}

static t_lexer	*set_tmp(t_data *data, size_t index)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	return (tmp);
}

void	modify_lxr_nds(t_data *data, t_substr *s, size_t index)
{
	t_lexer	*tmp;
	t_lexer	*buf;
	char	**ptr;

	buf = NULL;
	tmp = set_tmp(data, index);
	tmp->rm = 1;
	if (tmp->next != NULL)
	{
		buf = tmp->next;
		buf->prev = NULL;
	}
	ptr = ft_split(s->sub_m, ' ');
	if (!ptr)
		exit_error(data, "minishell: malloc error: ");
	add_node(data, &tmp, ptr[0], 0);
	add_buf_lxr_tail(data, s, buf, ptr);
	ft_free_pp(ptr);
}

int	check_space_expand(t_data *data, t_substr *s, size_t index)
{
	size_t	j;
	int		split;

	j = 0;
	split = 0;
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
