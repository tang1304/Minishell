/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/11 11:52:12 by rrebois          ###   ########lyon.fr   */
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
	int			status;
	t_command	*tmp;
	pid_t		i;

	tmp = data->cmd;
	while (tmp != NULL)
	{
		if (lstlencmd(data->cmd) == 1 && check_builtins(tmp->cmd) == SUCCESS)
			builtins(data, tmp->cmd);
		else
		{
			i = fork();
			if (i == 0)
			{
				if (check_builtins(tmp->cmd) == SUCCESS)
					builtins(data, tmp->cmd);
				//else
				exit(SUCCESS); // Child needs to free all
			}
			waitpid(i, &status, 0);
		}
		tmp = tmp->next;
	}
}
