/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 13:15:46 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	child_cretion(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < lstlencmd(data->cmd))
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return ;
			// ft_error(data);
		if (data->pids[i] == 0)
		{printf("Child N%ld\n", i + 1);
			valid_cmd(i, data);
			exit(CHILD_SUCCESS);
		}
		else
			wait_child(data);
		i++;
	}
}

void	pipe_creation(t_data *data)
{
	size_t	i;

	i = 0;
	data->pipes = (int **)malloc(sizeof(int *) * (lstlencmd(data->cmd) - 1));
	if (data->pipes == NULL)
		exit(1); //or not exit? if y with diff err code
	while (i < lstlencmd(data->cmd))
	{
		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (data->pipes[i] == NULL)
		{
			// free_all_pipes(data, i); TODO
			exit(2); // or not exit?? if y with diff err code
		}
		i++;
	}
	pids_creation(data);
}

void	pids_creation(t_data *data)
{
	size_t	i;

	i = 0;
	data->pids = malloc(sizeof(int) * lstlencmd(data->cmd)); // split here into 2 funcs
	if (data->pids == NULL)
	{
		// free_all_pipes(data, data->pipe_n);
		exit(3); // or not exit?? if y with diff err code
	}
	while (i < lstlencmd(data->cmd))
	{
		if (pipe(data->pipes[i]) == -1)
			exit(4);
			// free_everything(&data);
		i++;
	}
	extract_paths(data);
	child_cretion(data);
}

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
