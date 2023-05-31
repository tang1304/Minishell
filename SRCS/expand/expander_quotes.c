/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:22 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/31 11:10:05 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static char	*word_without_quotes(char *str, int i, int j)
{
	char	*new_word;
	int		k;
// printf("WORD LEN =%d\n", i);
	new_word = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_word)
		return (NULL);
	k = -1;
	while (++k < i)
	{//printf("Char b = %c|\n", str[k]);
		new_word[k] = str[k];
	}

	while (k < j)
	{
		new_word[k] = str[k + 1];//printf("Char m = %c|\n", str[k + 1]);
		k++;
	}
	while ((size_t)k < ft_strlen(str) - 2)
	{
		new_word[k] = str[k + 2];//printf("Char a = %c|\n", str[k + 2]);
		k++;
	}
	new_word[k] = '\0';
	free(str);
	return (new_word);
}

static int	quote_starting_point(char *str, int i)
{
	// int	j;
// printf("i beforer=%d\n", i);
	// j = 0;
	while (str[i])
	{//printf("char c = %c\n", str[i]);
		if (str[i] == '\'' || str[i] == '"')
			break ;
		// j++;
		i++;
	}//printf("WORD LEN =%d\n", i);
	return (i);
}

static int	quote_pairs(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1]) || (str[i] == '"' && str[i + 1]))
		{
			j++;
			i += quote_handling(str, i, str[i]) + 1;
		}
		else
			i++;
	}
	return (j);
}

char	*str_quotes_removal(char *str)
{
	int	i;
	int	j;
	int	k;
	int	q_pairs;
// printf("STR B =%s|\n", str);
	q_pairs = quote_pairs(str);
// printf("STR A =%s|\n", str);
// printf("q_pairs:%d\n", q_pairs);
	k = -1;
	i = 0;
	while (++k < q_pairs)
	{
		// printf("LA\n");
		i = quote_starting_point(str, i);
// printf("WORD LEN =%d\n", i);
		j = i++;
		// while (((str[i] != '"' && str[j] == '"') 
		// 		|| (str[i] != '\'' && str[j] == '\'')) && str[j] != '\0')
		while (str[j] != str[i] && str[j] != '\0')
		{
			j++;
		}
// printf("quotes-> word :%s\n", str);
		str = word_without_quotes(str, i - 1, j);
		// if (!new_word)
		// 	;
		// i--;
// printf("quotes-> word :%s\n", str);
	}
	return (str);
}

// int	quotes_removal(t_lexer *lexer)
// {
// 	t_lexer	*tmp;

// 	tmp = lexer;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->word == NULL || ((ft_strchr(tmp->word, '\'') == NULL
// 			&& ft_strchr(tmp->word, '"') == NULL)))
// 		{
// 			tmp = tmp->next;
// 			continue ;
// 		}
// 		tmp->word = str_quotes_removal(tmp->word);
// 		tmp = tmp->next;
// 	}
// 	return (1);
// }
