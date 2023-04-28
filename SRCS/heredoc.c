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
		if (ft_strncmp(line, data->hd->LIMITER[data->hd->heredoc], \
		ft_strlen(data->hd->LIMITER[data->hd->heredoc])) == 0 || !line)
			break ;
		buffer = ft_strjoin_free(buffer, line);
	}
	write(data->hd->fd[1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
	close(data->hd->fd[0]);
	close(data->hd->fd[1]);
	//free all!!! <Makefile ls |grep <<eof |wc >out
	// test bible non réalisée
}

void	check_heredoc(t_data *data)
{
	int		status;
	pid_t	i;

	data->hd->heredoc = 0;
	if (pipe(data->hd->fd) < 0) //Si erreur ->error message?? return?
		return ;
	while (data->hd->heredoc < data->hd->hd_count)
	{
		i = fork();
		if (i == 0)
		{
			init_heredoc(data);
			exit (SUCCESS); // faudra tout free
		}
		waitpid(i, &status, 0);
		data->hd->heredoc++;
	}
	// if (data->hd->hd_as_inf == 0)
		//close fd[0] et fd[1] + free LIMITER char **
}
