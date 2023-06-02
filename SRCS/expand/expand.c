/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/01 12:39:59 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//Attention si hdh"$USER"hdg -> 1 seul node donc quotes pas au début et à la fin

static char	*check_char(t_data *data, char *s, size_t *i, size_t index)
{
	t_substr	str;
	// char		*ptr;

	ft_bzero(&str, sizeof(t_substr));
	str.s = s;
	if (s[*i] == '$')
		expand_dollar(data, &str, i, index);
	else if (s[*i] == '\'')
		expand_quotes(data, &str, i, '\'');
	else
		expand_quotes(data, &str, i, '"');
	// ptr = ft_strdup(str.s);
	// free_struct_expand(&str);
	return (str.s);
}

void	expand(t_data *data)
{
	size_t	i;
	t_lexer	*tmp;

	data->svd_index = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->word != NULL)
		{
			while (tmp->word[i] != '\0')
			{
				if (tmp->word[i] == '$' && tmp->word[i + 1] && \
				tmp->word[i + 1] != ' ')
					tmp->word = check_char(data, tmp->word, &i, tmp->index);
				else if (tmp->word[i] == '\'')
					tmp->word = check_char(data, tmp->word, &i, tmp->index);
				else if (tmp->word[i] == '"')
					tmp->word = check_char(data, tmp->word, &i, tmp->index);
				else
					i++;
// printf("INDEX LXR = %ld INDEX SVD = %ld\n", tmp->index, data->svd_index);
				if (tmp->index != data->svd_index)
					tmp = update_tmp_index(data, &i);
			}
		}
		tmp = tmp->next;
		data->svd_index++;
	}
	// while (tmp->prev != NULL)
	// 	tmp = tmp->prev;
	// data->lexer = tmp;





// test
// 	size_t len = 0;
// 	if (lstlen(data->lexer) > 0)
// 	{

// 	tmp = data->lexer;
// 	while (tmp != NULL)
// 	{
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	printf("len lexer: %ld\n", len);

// 	t_data	*tmp2;
// 	tmp2 = data;
// 	while (tmp2->lexer != NULL)
// 	{
// 		ft_printf("\n\n");
// // if (tmp2->lexer->word != NULL)
// 	ft_printf("word node: %s\n", tmp2->lexer->word);
// // else
// 	ft_printf("token node: %s\n", tmp2->lexer->token);
// printf("index: %ld\n", tmp2->lexer->index);
// ft_printf("infile: %s\n", tmp2->lexer->infile);
// ft_printf("outfile: %s\n", tmp2->lexer->outfile);
// ft_printf("hdoc: %d\n",tmp2->lexer->hd_file);
// ft_printf("hdoc count: %d\n",tmp2->hd->hd_count);
// 		tmp2->lexer = tmp2->lexer->next;
// 	}}
// 	else
// 		printf("len lexer: %ld\n", len);
// 	// end test ls <TODO -l|wc -l >out>>out2<Makefile




		// test
// 	t_data	*tmp2;
// 	tmp2 = data;
// 	while (tmp2->lexer != NULL)
// 	{
// 		ft_printf("\n\n");
// if (tmp2->lexer->word != NULL)
// 	ft_printf("word node: %s\n", tmp2->lexer->word);
// else
// 	ft_printf("token node: %s\n", tmp2->lexer->token);
// printf("index: %ld\n", tmp2->lexer->index);
// ft_printf("infile: %s\n", tmp2->lexer->infile);
// ft_printf("outfile: %s\n", tmp2->lexer->outfile);
// ft_printf("LIMITER: %s\n",tmp2->lexer->LIMITER);
// ft_printf("hdoc: %d\n",tmp2->heredoc);
// 		tmp2->lexer = tmp2->lexer->next;
// 	}
	// end test
}
