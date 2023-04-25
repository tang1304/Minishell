/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:10:37 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/04 14:34:41 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// static void	add_node_cmd(t_data *data, char *cmd, char *args)
// {
// 	t_command	*new;
// 	t_command	*tmp;

// 	tmp = data->cmd;
// 	if (tmp != NULL)
// 		while (tmp->next != NULL)
// 			tmp = tmp->next;
// 	new = (t_command *)malloc(sizeof(*new));
// 	new->cmd = (char **)malloc(sizeof(char *) * 3);
// 	if (!new || !new->cmd)
// 	{
// 		printf("minishell: Error malloc\n");
// 		exit (NODE_FAILURE);
// 	}
// 	new->cmd[0] = cmd;
// 	new->cmd[1] = args;
// 	new->cmd[2] = NULL;
// 	if (data->cmd == NULL)
// 		data->cmd = new;
// 	else
// 		tmp->next = new;
// 	free(new);
// }

static int	cmd_check(t_data *data, char *cmd, char *args)
{(void)data;
	char	*command;
	char	*cmd_args;

	if (args != NULL)
	{
		command = ft_strjoin(cmd, " ");
		cmd_args = ft_strjoin(command, args);
		if (access(cmd_args , X_OK) == 0)//d'abord checker avec builtin puis access??
			ft_printf("%s: Valid cmd\n", cmd_args);
		else
			ft_printf("%s: Invalid cmd\n", cmd_args);
	}
	else
	{
		if (access(cmd , X_OK) == 0)//d'abord checker avec builtin puis access??
			ft_printf("%s: Valid cmd\n", cmd);
		else
			ft_printf("%s: Invalid cmd\n", cmd);
	}
	return (0);
}

void	create_cmd_struct(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0 \
		&& tmp->next->next != NULL)
			tmp = tmp->next->next;
		else if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0 \
		&& tmp->next->next == NULL)
			break ;
		if (tmp->word != NULL && tmp->prev != NULL && tmp->prev->token == NULL)
			cmd_check(data, tmp->prev->word, tmp->word);
		else if (tmp->word != NULL && tmp->prev != NULL && tmp->prev->token != NULL)
		{
			if (tmp->next != NULL && tmp->next->word != NULL)
				cmd_check(data, tmp->word, tmp->next->word);
			else if (tmp->next != NULL && tmp->next->word == NULL)
				cmd_check(data, tmp->word, NULL);
		}
		else if (tmp->word != NULL && tmp->next == NULL)
			cmd_check(data, tmp->word, NULL);
		tmp = tmp->next;
	}

	// while (data->cmd != NULL)
	// {
	// 	ft_printf("cmd: %s %s\n", data->cmd[0], data->cmd[1]);
	// 	data->cmd = data->cmd->next;
	// }
}
