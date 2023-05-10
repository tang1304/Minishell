/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:25:20 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 11:35:43 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_pp(char **ptr)
{
	size_t	x;

	x = 0;
	while (ptr[x] != 0)
	{
		free(ptr[x]);
		x++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_content_cmd_node(t_command *tmp)
{
	if (tmp->cmd != NULL)
		ft_free_pp(tmp->cmd);
	if (tmp->infile != NULL)
		free(tmp->infile);
	if (tmp->outfile != NULL)
		free(tmp->outfile);
	tmp->infile = NULL;
	tmp->outfile = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}
