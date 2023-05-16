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
				++data->hd->hd_count;
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
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, data->hd->LIMITER[data->hd->heredoc], \
		ft_strlen(data->hd->LIMITER[data->hd->heredoc])) == 0 || !line)
			break ;
		buffer = ft_strjoin_free(buffer, line);
	}
	write(data->hd->fd[data->hd->heredoc][1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
	close(data->hd->fd[data->hd->heredoc][0]);
	close(data->hd->fd[data->hd->heredoc][1]);
	//free all!!! <Makefile ls |grep <<eof |wc >out
	// test bible non réalisée
}

void	init_heredoc_data(t_data *data) // PB when only <Makefile or <<eof
{
	int			status;
	pid_t		i;

	data->hd->fd = (int **)malloc(sizeof(int *) * data->hd->hd_count);
	if (data->hd->fd == NULL)
		return ;//grbage val??

	data->hd->heredoc = 0;
	while (data->hd->heredoc < data->hd->hd_count)
	{
		data->hd->fd[data->hd->heredoc] = (int *)malloc(sizeof(int) * 2);
		if (data->hd->fd[data->hd->heredoc] == NULL)
			return ;//grbage val??
		if (pipe(data->hd->fd[data->hd->heredoc]) < 0)
			return ; //garbage val//Si erreur ->error message?? return?
		i = fork();
		if (i == 0)
		{printf("Hredoc N%ld\n", data->hd->hd_count);
			heredoc_pipe(data);
			exit (SUCCESS);
		}
		waitpid(i, &status, 0);
// read(tmp->fd[0], s, 5);
// write(1, s, ft_strlen(s));
		data->hd->heredoc++;
	}







	// if (pipe(data->hd->fd) < 0) //Si erreur ->error message?? return?
	// 	return ;
	// // if (data->hd->hd_count > 0)
	// // {
	// 	while (data->hd->heredoc < data->hd->hd_count)
	// 	{
	// 		i = fork();
	// 		if (i == 0)
	// 		{
	// 			init_heredoc(data);
	// 			exit (SUCCESS); // faudra tout free
	// 		}
	// 		waitpid(i, &status, 0);
	// 		data->hd->heredoc++;
	// 	}
	// 	// if (data->hd->hd_as_inf == 0)
	// 		//close fd[0] et fd[1] + free LIMITER char **
	// // }
}
