/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/25 16:45:51 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//Attention si hdh"$USER"hdg -> 1 seul node donc quotes pas au début et à la fin
//ls | "'$USER'" "user is $USER" "$USER $USER"     $USE'R'"$USER $USER"$USER
static char	*expand_str(t_data *data, char *s) //func too long
{
	size_t	j;
	char	*bef;
	char	*exp;
	char	*aft;
s = str_quotes_removal(s);
	bef = NULL;
	exp = NULL;
	aft = NULL;
	j = 0;
	while (s[j] != '\0')
	{
		if (s[j] == '$' && (ft_isalnum(s[j + 1]) == 1 || s[j + 1] == '?'))
		{
			j++;
			if (j > 0)
				bef = ft_substr(s, 0, j);
if (bef != NULL)
	printf("\n\n\nbef = %s c = %d\n", bef, bef[ft_strlen(bef) - 1]);
			while (ft_isalnum(s[j]) == 1 || s[j] == '?')//faire j = fonction et bien checker dans new func
				j++;//ou fonc si 0 alors ++ sinon break et chercher aussi $
				// if (s[j] == '$' && s[j - 1] && s[j - 1] != '$')
				// 	break ;




printf("j: %lu\n", j);
			aft = ft_substr(s, j, ft_strlen(s));
printf("aft = %s c = %d\n", aft, aft[ft_strlen(aft) - 1]);
			exp = ft_substr(s, ft_strlen(bef), j - ft_strlen(bef));
printf("exp = %s c = %d\n\n\n", exp, exp[ft_strlen(exp) - 1]);
			// s = get_var()
			exp = get_var(data, exp);
			j = ft_strlen(bef) + ft_strlen(exp);
			s = join_all(s, bef, exp, aft);
		}
		j++;
	}
	return (s);
}

static char	*expand_quotes(t_data *data, char *s, size_t *i, char c)
{
	char	*str_b;
	char	*str_m;
	char	*str_a;

	str_b = NULL;
	str_m = NULL;
	str_a = NULL;
	if (*i > 0)
		str_b = ft_substr(s, 0, *i);
	*i = *i + 1;
	while (s[*i] != c)
		*i = *i + 1;
	str_m = ft_substr(s, ft_strlen(str_b) + 1, *i);
	if (*i + 1 < ft_strlen(s))
		str_a = ft_substr(s, *i + 1, ft_strlen(s));
// printf("\n\nstr_b = %s\nstr_m = %s\nstr_a = %s\n\n", str_b, str_m, str_a);
	if (c == '"')
		str_m = expand_str(data, str_m);
	else
		str_m = str_quotes_removal(str_m);
	*i = ft_strlen(str_b) + ft_strlen(str_m);
// printf("OK\n");
	return (join_all(s, str_b, str_m, str_a));
}

static char	*check_char(t_data *data, char *s, size_t *i, int j)
{
	if (j == 0) // $
	{
		// if (s[*i + 1] && (ft_isalpha(s[*i + 1]) == 1 || s[*i + 1] == '?'))
		// 	s = expand_dollar(data, s, i);
		return (s);
	}
	else if (j == 1) // '
	{
		s = expand_quotes(data, s, i, '\'');
		return (s);
	}
	else
	{
		s = expand_quotes(data, s, i, '"');
		return (s);
	}
	return (s);
}

void	expand(t_data *data) // func too long
{
	size_t	i;
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->word == NULL)
			tmp = tmp->next;
		while (tmp->word[i] != '\0')
		{
			// if (tmp->word[i] == '$')
			// {
			// 	tmp->word = check_char(data, tmp->word, &i, 0);
			// }
			// else if (tmp->word[i] == '\'')
			// {
			// 	tmp->word = check_char(data, tmp->word, &i, 1);
			// }
			if (tmp->word[i] == '"')
			{
				tmp->word = check_char(data, tmp->word, &i, 2);
					// if ((int)i == -1)
					// 	return ;//ou ft_error....
			}
			i++;
		}
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
