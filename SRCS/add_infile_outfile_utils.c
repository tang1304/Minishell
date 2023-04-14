/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:32:38 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/14 13:37:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	add_infile(t_data *data, char *file, int i)
{
	t_lexer	*tmp;

	if (i == 2)
	{
		file = filename_quote_removal(file);
		file_check_access(data, file, i);
	}
	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (check_if_cmd(tmp->word) == SUCCESS)
		{
			if (tmp->infile != NULL && file != NULL && data->here_doc == 1)
				data->here_doc = 0;
			if (tmp->infile != NULL)
				free(tmp->infile);
			if (file != NULL)
				tmp->infile = file;
			else
				tmp->infile = data->LIMITER;
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_outfile(t_data *data, char *file, int i)
{
	t_lexer	*tmp;

	file = filename_quote_removal(file);
	file_check_access(data, file, i);
	tmp = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (1)
	{
		if (check_if_cmd(tmp->word) == SUCCESS)
		{
			if (tmp->outfile != NULL)
				free(tmp->outfile);
			tmp->outfile = file;
			return ;
		}
		tmp = tmp->prev;
	}
}

char	*remove_file(char *s, size_t i)
{
	size_t	start;
	int		j;
	char	*str;

	start = i;
	while (s[i] == '>' || s[i] == '<' || s[i] == ' ')
		i++;
	while (s[i] != ' ' && s[i] != '>' && s[i] != '<' && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(*str) * (ft_strlen(s) - i + start + 1));
	if (str == NULL)
		return (NULL);
	j = -1;
	while ((size_t)++j < start)
		str[j] = s[j];
	while (i < ft_strlen(s))
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (free(s), str);
}

int	check_if_cmd(char *s)
{
	size_t	i;
	int		token;

	i = 0;
	token = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i])
			i++;
		if (ft_isprint(s[i]) == 1 && s[i] != ' ' && s[i] != '>' && \
		s[i] != '<' && token == 0 && s[i] != '\0')
			return (SUCCESS);
		else if (ft_isprint(s[i]) == 1 && s[i] != ' ' && s[i] != '>' && \
		s[i] != '<' && token == 1 && s[i] != '\0')
		{
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
				i++;
			token = 0;
		}
		else if (s[i] != '>' || s[i] != '<')
			token = 1;
		if (s[i + 1] == '\0')
			i++;
	}
	return (NOT_WORD);
}

char	*get_filename(char *s, size_t i)
{
	size_t	start;
	size_t	j;
	char	*filename;

	j = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == '>' || s[i] == ' ' || s[i] == '<') && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '>' && s[i] != '<')
			i++;
		break ;
	}
	filename = (char *)malloc(sizeof(*filename) * (i - start + 1));
	if (filename == NULL)
		return (NULL);
	while (start < i)
	{
		filename[j] = s[start];
		start++;
		j++;
	}
	filename[j] = '\0';
	return (filename);
}
