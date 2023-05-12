/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/12 16:06:45 by tgellon          ###   ########lyon.fr   */
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

static void	heredoc_check(t_command *cmd)
{
	if (cmd->heredoc_file)
	{
		printf("\nheredoc\n");
		if (!cmd->cmd[0] || !cmd->cmd)
			return ;
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			return (perror("Error in heredoc dup2"));
		if (close(cmd->fd[0]) == -1)
			return (perror("Error in heredoc close"));
	}
}

static void	command_init(t_command *cmd)
{
	printf("ici\n");
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
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			return (perror("Error with stdout dup2"));
		if (close(cmd->fd[1]) == -1)
		return (perror("Error in child close"));
	}
	// if (cmd->pipe_b)
	// {
		// printf("\nPipe before\n");
	// 	dup2(cmd->fd[0], STDIN_FILENO);
	// 	if (close(cmd->fd[0] == -1))
	// 		return (perror("Error in child close"));
	// }
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
			if (pipe(tmp->fd) == -1)	
				perror("Pipe error");
			i = fork();
			if (i == 0)
			{
				if (check_builtins(tmp->cmd) == SUCCESS && tmp->next == NULL)
					builtins(data, tmp->cmd);
				else
				{
					command_init(tmp);
					exec(data, tmp->cmd);
				}
				exit(SUCCESS); // Child needs to free all
			}
			printf("parent\n");
			if (dup2(tmp->fd[0], STDIN_FILENO) == -1)
				return (perror("Error with parent dup2"));
			waitpid(i, &status, 0);
		}
		tmp = tmp->next;
	}
}
