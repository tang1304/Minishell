/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/11 07:51:50 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	extract_paths(t_data *data)
{
	char	*s;
	char	**ptr;
	int		j;

	j = 0;
	s = NULL;
	while (data->envp[j] != 0)
	{
		s = ft_strnstr(data->envp[j], "PATH=", 5);
		if (s != NULL)
			break ;
		j++;
	}
	if (s != NULL)
	{
		ptr = ft_split(s, '=');
		data->paths = ft_split(ptr[1], ':');
		ft_free_pp(ptr);
	}
}

void	exec_cmd_lst(t_data *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp != NULL)
	{
		if (builtins(data, tmp->cmd) == SUCCESS)
			tmp = tmp->next;
		else
		{

		}
	}
}
