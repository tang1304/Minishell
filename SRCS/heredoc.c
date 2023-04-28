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
	data->hd->hd_count = 0;
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
	if (data->hd->hd_count > 0)
	{
		data->hd->LIMITER = (char **)malloc(sizeof(char *) * \
		(data->hd->hd_count + 1));
		// if (data->LIMITER == NULL)
		// 	return error??;
	}
	data->hd->LIMITER[data->hd->hd_count] = 0;
}

void	init_heredoc(t_data *data)
{
	char	*line;
	char	*buffer;

	buffer = calloc(sizeof(*buffer), 1);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)) == 0 || add slash
		!line)
			break ;
		buffer = ft_strjoin_free(buffer, line);
	}
	write(data->fd[1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
	close(data->fd[0]);
	close(data->fd[1]);
	//free all!!! <Makefile ls |grep <<eof |wc >out
	// test bible non réalisée
}

void	check_heredoc(t_data *data)
{
	int		status;
	pid_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	if (data->heredoc == 0)
		return ;
	while (tmp != NULL)
	{
		if (tmp->LIMITER != NULL)
		{
			data->LIMITER = tmp->LIMITER;
			break ;
		}
		tmp = tmp->next;
	}
	if (pipe(data->fd) < 0) //Si erreur ->error message
		return ;
	i = fork();
	if (i == 0)
		init_heredoc(data);
	waitpid(i, &status, 0);
	// if (data->here_doc == 0)

	// if (tmp->infile != NULL) A ajouter car si: ls <TODO <<eof <Makefile
	// Makefile est le infile mais le heredoc est lancé également
	// 	close_fds();
}
