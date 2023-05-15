/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/15 11:43:58 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// void	child_cretion(t_data *data)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < lstlencmd(data->cmd))
// 	{
// 		data->pids[i] = fork();
// 		if (data->pids[i] == -1)
// 			return ;
// 			// ft_error(data);
// 		if (data->pids[i] == 0)
// 		{printf("Child N%ld\n", i + 1);
// 			// valid_cmd(i, data);
// 			exit(CHILD_SUCCESS);
// 		}
// 		else
// 			wait_child(data);
// 		i++;
// 	}
// }

// void	pipe_creation(t_data *data)
// {
// 	size_t	i;

// 	i = 0;
// 	data->pipes = (int **)malloc(sizeof(int *) * (lstlencmd(data->cmd) - 1));
// 	if (data->pipes == NULL)
// 		exit(1); //or not exit? if y with diff err code
// 	while (i < lstlencmd(data->cmd))
// 	{
// 		data->pipes[i] = (int *)malloc(sizeof(int) * 2);
// 		if (data->pipes[i] == NULL)
// 		{
// 			// free_all_pipes(data, i); TODO
// 			exit(2); // or not exit?? if y with diff err code
// 		}
// 		i++;
// 	}
// 	pids_creation(data);
// }

// void	pids_creation(t_data *data)
// {
// 	size_t	i;

// 	i = 0;
// 	data->pids = malloc(sizeof(int) * lstlencmd(data->cmd)); // split here into 2 funcs
// 	if (data->pids == NULL)
// 	{
// 		// free_all_pipes(data, data->pipe_n);
// 		exit(3); // or not exit?? if y with diff err code
// 	}
// 	while (i < lstlencmd(data->cmd))
// 	{
// 		if (pipe(data->pipes[i]) == -1)
// 			exit(4);
// 			// free_everything(&data);
// 		i++;
// 	}
// 	extract_paths(data);
// 	child_cretion(data);
// }


void	extract_paths(t_data *data)
{
	char	*s;
	t_env	*tmp;

	tmp = data->env;
	s = NULL;
	while (tmp)
	{
		s = search_env(data, "PATH=");
		if (s != NULL)
			break ;
		tmp = tmp->next;
	}
	if (s != NULL)
	{
		data->paths = ft_split(s, ':');
		// if (!data->paths)
		// 	return ();
	}
}

static void	command_init(t_data *data, t_command *cmd)
{
	close(data->pipe[0]);
	if (!cmd->cmd[0])
		return ;
	if (cmd->fdin > 0 && !cmd->heredoc_file)
	{
		printf("\nfdin\n");
		if (dup2(cmd->fdin, STDIN_FILENO) == -1)
			return (perror("Error with infile dup2"));
	}
	if (cmd->fdout > 0)
	{
		printf("\nfdout\n");
		if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
			return (perror("Error with outfile dup2"));
	}
	else if (cmd->fdout == 0 && cmd->pipe_a)
	{
		printf("\nNo fdout, Pipe after\n");
		if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
			return (perror("Error with stdout dup2"));
		if (close(data->pipe[1]) == -1)
			return (perror("Error in child close"));
	}
}

void	exec_cmd_lst(t_data *data)
{
	int			status;
	t_command	*tmp;
	pid_t		i;

	tmp = data->cmd;
	while (tmp)
	{
		heredoc_check(tmp);
		if (lstlencmd(data->cmd) == 1 && check_builtins(tmp->cmd) == SUCCESS)
			builtins(data, tmp->cmd);
		else
		{
			if (pipe(data->pipe) == -1)
				perror("Pipe error");
			i = fork();
			if (i == 0)
			{
				if (check_builtins(tmp->cmd) == SUCCESS && tmp->next == NULL)
					builtins(data, tmp->cmd);
				else
				{
					command_init(data, tmp);
					exec(data, tmp->cmd);
				}
				exit(SUCCESS); // Child needs to free all
			}
			else
			{
				if (tmp->pipe_a == 1)
					close(data->pipe[1]);
				if (dup2(data->pipe[0], STDIN_FILENO) == -1)
					return (perror("Error with parent dup2"));
				close(data->pipe[0]);
			}
			waitpid(i, &status, 0);
		}
		tmp = tmp->next;
	}
}
