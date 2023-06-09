/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:53:32 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 08:57:27 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	exit_error(t_data *data, char *str)
{
	if (str)
		perror(str);
	free_all(data);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close_all(data);
	exit(EXIT_FAILURE);
}

void	expand_error(t_data *data, t_substr *s, char *str)
{
	if (str)
		perror(str);
	free_all(data);
	free_substr_strct(s);
	close(data->pipe[0]);
	close(data->pipe[1]);
	close_all(data);
	exit(EXIT_FAILURE);
}

void	ascii_check(t_data *data, char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 0 || str[i] > 126)
			exit_error(data, "minishell: non ASCII char");
	}
}
