/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:28:26 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/16 10:53:50 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	restore_stds(t_data *data)
{
	if (dup2(data->stdin_save, STDIN_FILENO) == -1 \
	|| dup2(data->stdout_save, STDOUT_FILENO) == -1)
		return (perror("Error with restoring STDIN/STDOUT dup2"));
	// if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
	// 	return (perror("Error with closing STDIN/STDOUT saves"));
	// close a la fin du programme, ou initialiser a chaque boucle
}

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

/* Si multiples infiles/heredocs, prendre le dernier. Mais si une erreur d'open/nom
etc, ne prends aucuns in et saute la commande
Si pipe et outfile, envoi cmd dans outfile*/
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

static void	forking(t_data *data, t_command *cmd, int i)
{
	if (i == 0)
	{
		if (check_builtins(cmd->cmd) == SUCCESS && cmd->next == NULL)
			builtins(data, cmd->cmd);
		else
		{
			command_init(data, cmd);
			exec(data, cmd->cmd);
		}
		exit(SUCCESS); // Child needs to free all
	}
	else
	{
		if (cmd->pipe_a == 1)
			close(data->pipe[1]);
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			return (perror("Error with parent dup2"));
		close(data->pipe[0]);
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
		{
			builtins(data, tmp->cmd);
			return ;
		}
		else
		{
			if (pipe(data->pipe) == -1)
				perror("Pipe error");
			i = fork();
			forking(data, tmp, i);
			waitpid(i, &status, 0);
		}
		tmp = tmp->next;
	}
	restore_stds(data);
}
