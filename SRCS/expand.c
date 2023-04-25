/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/25 09:45:47 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//Attention si hdh"$USER"hdg -> 1 seul node donc quotes pas au début et à la fin
//ls | "'$USER'" "user is $USER" "$USER $USER"
static char	*expand_str(t_data *data, char *s) //func too long
{
	size_t	j;
	char	*bef;
	char	*exp;
	char	*aft;

	bef = NULL;
	exp = NULL;
	aft = NULL;
	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] == '$' && s[j + 1] != ' ' && ft_isprint(s[j + 1]) == 1 && \
		s[j + 1] != '\0')
		{
			if (j > 0)
				bef = ft_substr(s, 0, j);
// if (bef != NULL)
	// printf("\n\n\nbef = %s c = %d\n", bef, bef[ft_strlen(bef) - 1]);
			while (s[j] != ' ' && s[j] != '\0' && s[j] != '\'')
				j++;//ou fonc si 0 alors ++ sinon break et chercher aussi $
				// if (s[j] == '$' && s[j - 1] && s[j - 1] != '$')
				// 	break ;




// printf("char stopped: %c\n", s[j]);
			aft = ft_substr(s, j, ft_strlen(s));
// printf("aft = %s c = %d\n", aft, aft[ft_strlen(aft) - 1]);
			exp = ft_substr(s, ft_strlen(bef) + 1, j - ft_strlen(bef) - 1);
// printf("exp = %s c = %d\n\n\n", exp, exp[ft_strlen(exp) - 1]);
			// s = get_var()
			exp = get_var(data, exp);
			j = ft_strlen(bef) + ft_strlen(exp);
			s = join_all(s, bef, exp, aft);
		}
		j++;
	}
	return (s);
}

static char	*expand_d_quotes(t_data *data, char *s, size_t *i)
{
	char	*str_b;
	char	*str_m;
	char	*str_a;
	size_t	j;

	str_b = NULL;
	str_m = NULL;
	str_a = NULL;
	if (*i > 0)
		str_b = ft_substr(s, 0, *i);
	j = *i + 1;
	while (s[j] != '"')
		j++;
	str_m = ft_substr(s, *i + 1, j - *i - 1);
	if (j + 1 < ft_strlen(s))
		str_a = ft_substr(s, j + 1, ft_strlen(s));
// printf("\n\nstr_b = %s\nstr_m = %s\nstr_a = %s\n\n", str_b, str_m, str_a);
	str_m = expand_str(data, str_m);
	*i = ft_strlen(str_b) + ft_strlen(str_m);
	s = join_all(s, str_b, str_m, str_a);
// printf("OK\n");
	return (s);
}

static size_t	check_dollar_sign(char *s, size_t start)
{
	size_t	count;

	count = 0;
	while (s[start] != '"')
	{
		if (s[start] == '$')
			count++;
		start++;
	}
	return (count);
}

void	expand(t_data *data) // func too long
{
	int		expand;
	size_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
		expand = 0;
		if (tmp->word == NULL)
			tmp = tmp->next;
		while (tmp->word[i] != '\0')
		{
			if (tmp->word[i] == '\'')
				i += quote_handling(tmp->word, i, tmp->word[i]) + 1;
			if (tmp->word[i] == '"')
			{
				if (check_dollar_sign(tmp->word, i + 1) != 0)
				{
					expand = 1;
					tmp->word = expand_d_quotes(data, tmp->word, &i);
					// if ((int)i == -1)
					// 	return ;//ou ft_error....
				}
				else
					i += quote_handling(tmp->word, i, tmp->word[i]) + 1;
			}
			i++;
		}
		if (expand == 0)
			tmp->word = str_quotes_removal(tmp->word);
		tmp = tmp->next;
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