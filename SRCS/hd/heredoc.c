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

int	heredoc_ctrl_check(t_data *data, char *line, char *buffer)
{
	if (g_status != 130 && line == NULL)
	{
		printf("minishell: warning: here-document at line %ld delimited by \
end-of-file (wanted `%s')\n", data->ctrl_d_val, \
		data->hd->limiter[data->hd->heredoc]);
		free(buffer);
		return (HD_CTRL_D);
	}
	else if (g_status == 130)
	{
		free(buffer);
		return (HD_CTRL_C);
	}
	else
		return (SUCCESS);
}

static int	event(void)
{
	return (0);
}

void	heredoc_pipe(t_data *data)
{
	char	*line;
	char	*buffer;

	buffer = ft_calloc(sizeof(*buffer), 1);
	signal_hd_set();
	g_status = 0;
	while (g_status != 130)
	{
		line = readline("> ");
		rl_event_hook = event;
		if ((ft_strncmp(line, data->hd->limiter[data->hd->heredoc], \
		ft_strlen(line)) == 0 && ft_strlen(line) == \
		ft_strlen(data->hd->limiter[data->hd->heredoc])))
			break ;
		if (heredoc_ctrl_check(data, line, buffer) != SUCCESS)
			return ;
		line = expand_line(data, line, buffer);
		buffer = ft_strjoin_free(data, buffer, line);//si malloc err leak in expand_line
	}
	write(data->hd->fd[data->hd->heredoc][1], buffer, ft_strlen(buffer));
	free(buffer);
	if (line)
		free(line);
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
	create_pipes_hd(data);
	silence_signals();
	while (data->hd->heredoc < data->hd->hd_count)
	{
		heredoc_pipe(data);
		data->hd->heredoc++;
		data->ctrl_d_val++;
	}
	signal_set();
	data->hd->heredoc = 0;
}
