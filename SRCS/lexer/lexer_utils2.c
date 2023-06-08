/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:40:14 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 15:43:13 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	config_node(t_data *data, char *str, t_lexer *node, int i)
{
	if (i == 0)
	{
		node->word = ft_strdup(str);
		if (!node->word)
		{
			free(node);
			exit_error(data, "minishell: malloc error : ");
		}
		node->hd_number = -1;
	}
	else
	{
		node->token = ft_strdup(str);
		if (!node->token)
		{
			free(node);
			exit_error(data, "minishell: malloc error : ");
		}
	}
}
