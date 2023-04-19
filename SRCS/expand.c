/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:06 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/19 20:18:58 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//Attention si hdh"$USER"hdg -> 1 seul node donc quotes pas au début et à la fin
// static char	*remove_single_quotes(char *s, size_t i)//add char c comme ça utilisable par ' et "?
// {
// 	char	*cpy;
// 	size_t	j;
// 	size_t	x;
// 	size_t	y;

// 	y = 0;
// 	x = 0;
// 	j = i;
// 	while (s[i] != '\'')
// 		i++;
// 	cpy = (char *)malloc(sizeof(*cpy) * (ft_strlen(s) - 1));
// 	if (cpy == NULL)
// 		return (NULL);
// 	while (x < ft_strlen(s) - 2)
// 	{
// 		if (x == j || x == i)
// 			y++;
// 		cpy[x] = s[y];
// 		y++;
// 		x++;
// 	}
// 	cpy[x] = '\0';
// 	return (free(s), s = NULL, cpy);
// }

void	expand(t_data *data)
{
	size_t	i;
	t_lexer	*tmp;

	i = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		while (tmp->word[i] != '\0')
		{
			if (tmp->word[i] == '\'')
			{
				// i += quote_handling(tmp->word, i, tmp->word[i]) - 2;
				tmp->word = str_quotes_removal(tmp->word);
			}
			if (tmp->word[i] == '"')
			{
				// if (check_dollar(tmp->word, i) == 0)
				// 	tmp->word = str_quotes_removal(tmp->word);
				// else
				// i += quote_handling(tmp->word, i, tmp->word[i]) - 2;
				tmp->word = str_quotes_removal(tmp->word);
				// tmp->word = str_expand(tmp->word);
			}
			i++;
		}

		// else
		// 	str_quotes_removal(tmp->word);

			//search for $
			//si $ expand
			//else suppr ""

		tmp = tmp->next;
		// si quotes ailleurs entre les cmd a enlever aussi
	}






		// test
	t_data	*tmp2;
	tmp2 = data;
	while (tmp2->lexer != NULL)
	{
		ft_printf("\n\n");
if (tmp2->lexer->word != NULL)
	ft_printf("word node: %s\n", tmp2->lexer->word);
else
	ft_printf("token node: %s\n", tmp2->lexer->token);
printf("index: %ld\n", tmp2->lexer->index);
ft_printf("infile: %s\n", tmp2->lexer->infile);
ft_printf("outfile: %s\n", tmp2->lexer->outfile);
ft_printf("LIMITER: %s\n",tmp2->lexer->LIMITER);
ft_printf("hdoc: %d\n",tmp2->heredoc);
		tmp2->lexer = tmp2->lexer->next;
	}
	// end test
}
