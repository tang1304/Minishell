/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:10:46 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/18 11:10:46 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	data->hd->LIMITER = (char **)malloc(sizeof(char *) * \
	(data->hd->hd_count + 1));
		// if (data->LIMITER == NULL)
		// 	return error??;
	data->hd->LIMITER[data->hd->hd_count] = 0;
}

void	heredoc_pipe(t_data *data)
{
	char	*line;
	char	*buffer;

	buffer = calloc(sizeof(*buffer), 1);
	signal_hd_set();
	while (1)
	{
		line = readline("> ");
		if ((ft_strncmp(line, data->hd->LIMITER[data->hd->heredoc], ft_strlen\
		(line)) == 0 && ft_strlen(data->hd->LIMITER[data->hd->heredoc]) == \
		ft_strlen(line)) \
		|| !line)
			break ;
		line = expand_line(data, line);
		buffer = ft_strjoin_free(buffer, line);
	}
	write(data->hd->fd[data->hd->heredoc][1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
	close_all(data);
	free_all(data);
}

void	create_pipes_hd(t_data *data)
{
	data->hd->fd = (int **)malloc(sizeof(int *) * data->hd->hd_count);
	if (data->hd->fd == NULL)
		return ;//grbage val??
	while (data->hd->heredoc < data->hd->hd_count)
	{
		data->hd->fd[data->hd->heredoc] = (int *)malloc(sizeof(int) * 2);
		if (data->hd->fd[data->hd->heredoc] == NULL)
			return ;//grbage val??
		data->hd->heredoc++;
	}
	data->hd->heredoc = 0;
	while (data->hd->heredoc < data->hd->hd_count)
	{//printf("LOOOOOOOOOP!!!\n");
		if (pipe(data->hd->fd[data->hd->heredoc]) < 0)
			return ;//grbage val??
		data->hd->heredoc++;
	}
	data->hd->heredoc = 0;
}

void	init_heredoc_data(t_data *data)
{
	int			status;
	pid_t		i;

	create_pipes_hd(data);
	while (data->hd->heredoc < data->hd->hd_count)
	{
		i = fork();
		if (i == 0)
		{
			heredoc_pipe(data);
			exit (SUCCESS);
		}
		waitpid(i, &status, 0);
		data->hd->heredoc++;
	}
	data->hd->heredoc = 0;
}
