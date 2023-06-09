/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:03:57 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/09 08:20:17 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_change_str(t_data *data, char *s1, char *s2)
{
	char	*new;
	int		i;

	free(s1);
	new = malloc(sizeof(char) * (ft_strlen(s2) + 1));
	if (!new)
		exit_error(data, "minishell: malloc error: ");
	i = 0;
	while (s2[i])
	{
		new[i] = s2[i];
		i++;
	}
	return (new);
}

size_t	lstlen(t_lexer *lexer)
{
	size_t	len;
	t_lexer	*tmp;

	len = 0;
	if (!lexer)
		return (0);
	tmp = lexer;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

size_t	lstlencmd(t_command *cmd)
{
	size_t		len;
	t_command	*tmp;

	len = 0;
	if (!cmd)
		return (0);
	tmp = cmd;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	complete_inf_data(t_data *data, t_lexer *tmp, char *file, int valid)
{
	if (tmp->infile != NULL)
	{
		free(tmp->infile);
		tmp->infile = NULL;
	}
	tmp->fdin = data->fdin;
	tmp->hd_file = 0;
	tmp->hd_number = -1;
	if (valid == 0)
	{
		add_file_node(data, tmp, file, 0);
		return ;
	}
	else
	{
		tmp->inf_err = 1;
		return ;
	}
}
