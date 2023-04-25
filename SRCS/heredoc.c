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

void	init_heredoc(t_data *data)
{
	char	*line;
	char	*buffer;

	buffer = calloc(sizeof(*buffer), 1);
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER)) == 0 || \
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
	// if (tmp->infile != NULL) A ajouter car si: ls <TODO <<eof <Makefile
	// Makefile est le infile mais le heredoc est lancé également
	// 	close_fds();
}
