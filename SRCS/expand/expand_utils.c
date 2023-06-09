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

static int	pre_adding_nodes(t_data *data, t_substr *s, char **ptr)
{
	size_t	j;

	j = 1;
	while (ptr[j] != 0)
	{
		if (!add_node(&data->lexer, ptr[j], 0))
			return (0);
		j++;
	}
	if (ft_strlen(s->sub_a) > 0)
	{
		if (!add_node(&data->lexer, s->sub_a, 0))
			return (0);
	}
	return (1);
}

static int	add_buf_lxr_tail(t_data *data, t_substr *s, t_lexer *buf, \
							char **ptr)
{
	t_lexer	*tmp;

	if (!pre_adding_nodes(data, s, ptr))
		return (0);
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
	return (1);
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
		exit_error(data, "minishell: malloc error ");
	if (!add_node(&tmp, ptr[0], 0))
	{
		ft_free_pp(ptr);
		exit_error(data, "minishell: malloc error ");
	}
	if (!add_buf_lxr_tail(data, s, buf, ptr))
	{
		ft_free_pp(ptr);
		exit_error(data, "minishell: malloc error ");
	}
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
