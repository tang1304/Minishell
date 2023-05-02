/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:03:57 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/02 14:44:25 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = ((char *)s2)[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (free(s1), free(s2), ptr);
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
		data->hd->hd_as_inf = 0;
	}
	if (valid == 0)
	{
		add_file_node(data, tmp, file, 0);//0 infile 1hd
		return ;
	}
	else
	{
		tmp->inf_err = 1;
		return ;
	}
}

void	complete_out_data(t_lexer *tmp, char *file, int valid)
{
	if (tmp->outfile != NULL)
		free(tmp->outfile);
	if (valid == 0)
	{
		tmp->outfile = ft_strdup(file);
		return ;
	}
	else
	{
		tmp->out_err = 1;
		return ;
	}
}
