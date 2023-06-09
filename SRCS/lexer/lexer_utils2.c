/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:44:49 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 09:45:37 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	config_node(char *str, t_lexer *node, int i)
{
	if (i == 0)
	{
		node->word = ft_strdup(str);
		if (!node->word)
			return (ERR_NODE);
		node->hd_number = -1;
	}
	else
	{
		node->token = ft_strdup(str);
		if (!node->token)
			return (ERR_NODE);
	}
	return (SUCCESS);
}