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

void	init_heredoc(t_data *data, t_command *cmd)
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
	write(cmd->fd[1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	//free all!!! <Makefile ls |grep <<eof |wc >out
	// test bible non réalisée
}

void	check_heredoc(t_data *data)
{
	int			status;
	t_command	*tmp;
	pid_t		i;
// char	*s;
// s=NULL;
	tmp = data->cmd;
	data->hd->heredoc = 0;
	while (tmp != NULL)
	{
		if (tmp->heredoc_file == 1)
		{
			if (pipe(tmp->fd) < 0) //Si erreur ->error message?? return?
				return ;
			while ((int)data->hd->heredoc <= tmp->heredoc_num)
			{
				i = fork();
				if (i == 0)
				{
					init_heredoc(data, tmp);
					exit (SUCCESS);
				}
				waitpid(i, &status, 0);
// read(tmp->fd[0], s, 5);
// write(1, s, ft_strlen(s));
				data->hd->heredoc++;
			}
		}
		tmp = tmp->next;
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
