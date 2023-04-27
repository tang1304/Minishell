/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:45:08 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 11:18:05 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//Attention si hdh"$USER"hdg -> 1 seul node donc quotes pas au début et à la fin
//ls | "'$USER'" "user is $USER" "$USER $USER"     $USE'R'"$USER $USER"$USER

static char	*expand_str(t_data *data, t_substr *s) //func too long
{
	size_t	j;

printf("string: %s\n", s->middle);
	j = 0;
	while (s->middle[j] != '\0')
	{
		if (s->middle[j] == '$' && (ft_isalpha(s->middle[j + 1]) == 1 || \
		s->middle[j + 1] == '?'))
		{
			j++;
			if (j > 0)
				s->sub_b = ft_substr(s->middle, 0, j - 1);
if (s->sub_b != NULL)
	printf("\n\n\nbef = %s c = %d\n", s->sub_b, s->sub_b[ft_strlen(s->sub_b) - 1]);
			while (ft_isalnum(s->middle[j]) == 1)// faire 2 func e plus si j = ? ou j = alnum
				j++;//ou fonc si 0 alors ++ sinon break et chercher aussi $
				// if (s[j] == '$' && s[j - 1] && s[j - 1] != '$')
				// 	break ;




printf("char stopped: %d=%c\n", s->middle[j], s->middle[j]);
			s->sub_a = ft_substr(s->middle, j, ft_strlen(s->middle) - j);
printf("aft = %s c = %d\n", s->sub_a, s->sub_a[ft_strlen(s->sub_a) - 1]);
			s->sub_m = ft_substr(s->middle, ft_strlen(s->sub_b), j - (ft_strlen(s->sub_b)));
printf("exp = %s c = %d\n\n\n", s->sub_m, s->sub_m[ft_strlen(s->sub_m) - 1]);
			s->sub_m = get_var(data, s->sub_m);
			j = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
			s->middle = join_all(s->middle, s->sub_b, s->sub_m, s->sub_a);
		}
		else
			j++;
	}
	return (s->middle);
}

static char	*expand_quotes(t_data *data, t_substr *str, size_t *i, char c)//marche bien now
{
	size_t	j;

	j = *i + 1; // point to first char after opening ' or "
	if (*i > 0)
		str->before = ft_substr(str->s, 0, *i);
	*i = *i + 1;
	while (str->s[*i] != c)
		*i = *i + 1; // Here *i value point to closing ' or "
	str->middle = ft_substr(str->s, j, *i - j);
	if (*i + 1 < ft_strlen(str->s))
		str->after = ft_substr(str->s, *i + 1, ft_strlen(str->s));
printf("\n\nstr_b = %s\nstr_m = %s\nstr_a = %s\n\n", str->before, str->middle, str->after);
	if (c == '"')
		str->middle = expand_str(data, str);
	else
		str->middle = str_quotes_removal(str->middle);
	*i = ft_strlen(str->before) + ft_strlen(str->middle);
	str->s = join_all(str->s, str->before, str->middle, str->after);
	return (str->s);
}

static char	*check_char(t_data *data, char *s, size_t *i, int j)
{
	t_substr	str;

	str.s = s;
	str.before = NULL;
	str.middle = NULL;
	str.after = NULL;
	str.sub_b = NULL;
	str.sub_m = NULL;
	str.sub_a = NULL;
	if (j == 0) // $
	{
		// if (s[*i + 1] && (ft_isalpha(s[*i + 1]) == 1 || s[*i + 1] == '?'))
		// 	s = expand_dollar(data, s, i);
		return (s);
	}
	else if (j == 1) // '
	{
		s = expand_quotes(data, &str, i, '\'');
	}
	else
	{
		s = expand_quotes(data, &str, i, '"');
	}
	return (str.s);
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
