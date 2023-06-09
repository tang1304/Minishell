/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:37:02 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 16:31:51 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	heredoc_redir(t_data *data)
{
	t_lexer	*tmp;

	heredoc_count(data);
	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "<<", 2) == 0 \
		&& ft_strlen(tmp->token) == 2)
		{
			data->hd->limiter[data->hd->heredoc] = ft_strdup(tmp->next->word);
			if (!data->hd->limiter[data->hd->heredoc])
				exit_error(data, "minishell: malloc error");
			data->hd->heredoc++;
		}
		tmp = tmp->next;
	}
	data->hd->heredoc = 0;
	prepare_expand_hd(data);
	init_heredoc_data(data);
	return (SUCCESS);
}

void	add_heredoc(t_data *data, char *file, size_t index)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	tmp = find_start(tmp);
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
			break ;
		if ((tmp->word != NULL && tmp->prev == NULL) || (tmp->word != NULL \
		&& tmp->prev->word != NULL) || (tmp->word != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0))
		{
			if (tmp->infile != NULL)
				tmp->hd_file = 0;
			add_file_node(data, tmp, file, 1);
			return ;
		}
		tmp = tmp->next;
	}
	add_file_node(data, tmp, file, 2);
}

void	heredoc_count(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL)
		{
			if (ft_strncmp(tmp->token, "<<", 2) == 0 && \
			ft_strlen(tmp->token) == 2)
				data->hd->hd_count++;
		}
		tmp = tmp->next;
	}
	if (data->hd->hd_count > 1024)
		free_hd_limit(data);
	data->hd->limiter = (char **)malloc(sizeof(char *) * \
	(data->hd->hd_count + 1));
	if (data->hd->limiter == NULL)
		exit_error(data, "minishell: malloc error: ");
	data->hd->limiter[data->hd->hd_count] = 0;
}
