/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:10:46 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/18 11:10:46 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*ft_strjoin_heredoc(char *s1, char *s2)
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

void	init_heredoc(t_data *data)
{
	char	*line;
	char	*buffer;

	buffer = malloc(sizeof(*buffer));
	if (buffer == NULL)
		return ;
	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, data->LIMITER, ft_strlen(data->LIMITER) == 0))
			break ;
		buffer = ft_strjoin_heredoc(buffer, line);
	}
	printf("heredoc working!!\n");
}

void	check_heredoc(t_data *data)
{
	pid_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	if (data->heredoc == 0)
		return ;
	while (tmp != NULL)
	{
		if (tmp->LIMITER != NULL)
		{
			data->LIMITER = tmp->LIMITER;
			break ;
		}
		tmp = tmp->next;
	}
	if (pipe(data->fd) < 0) //Si erreur, on free all??exit??
		return ;
	i = fork();
	if (i == 0)
		init_heredoc(data);
}
