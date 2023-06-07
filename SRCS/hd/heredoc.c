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
	if (data->hd->hd_count > 1024)
		free_hd_limit(data);
	data->hd->limiter = (char **)malloc(sizeof(char *) * \
	(data->hd->hd_count + 1));
	if (data->hd->limiter == NULL)
		exit_error(data, "minishell: malloc error ");
	data->hd->limiter[data->hd->hd_count] = 0;
}

void	heredoc_ctrl_d(t_data *data, char *line, char *buffer)
{
	printf("minishell: warning: here-document at line %ld delimited by \
end-of-file (wanted `%s')\n", data->ctrl_d_val, \
data->hd->limiter[data->hd->heredoc]);
	free(buffer);
	if (line)
		free(line);
	close_all(data);
	free_all(data);
	exit (SUCCESS);
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
		if ((ft_strncmp(line, data->hd->limiter[data->hd->heredoc], \
		ft_strlen(line)) == 0 && ft_strlen(line) == \
		ft_strlen(data->hd->limiter[data->hd->heredoc])))
			break ;
		if (line == NULL)
			heredoc_ctrl_d(data, line, buffer);
		line = expand_line(data, line);
		buffer = ft_strjoin_free(data, buffer, line);
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
		exit_error(data, "minishell: malloc error ");
	while (data->hd->heredoc < data->hd->hd_count)
	{
		data->hd->fd[data->hd->heredoc] = (int *)malloc(sizeof(int) * 2);
		if (data->hd->fd[data->hd->heredoc] == NULL)
			exit_error(data, "minishell: malloc error ");
		data->hd->heredoc++;
	}
	data->hd->heredoc = 0;
	while (data->hd->heredoc < data->hd->hd_count)
	{
		if (pipe(data->hd->fd[data->hd->heredoc]) < 0)
			exit_error(data, "minishell: pipe error ");
		data->hd->heredoc++;
	}
	data->hd->heredoc = 0;
}

void	init_heredoc_data(t_data *data)
{
	int			status;
	pid_t		i;

	create_pipes_hd(data);
	silence_signals();
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
		data->ctrl_d_val++;
	}
	signal_set();
	data->hd->heredoc = 0;
}
