/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/31 09:49:24 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//$USER"$USER '$USER'"'USER' ok

void	question_mark(t_data *data, t_substr *s, size_t *i, size_t index)
{
	// char	*buf;

	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	// buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	// s->sub_m = ft_itoa(g_status);
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

void	number_xpd(t_data *data, t_substr *s, size_t *i, size_t index)
{
	char	*buf;

	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
// printf("STRING BEFORE = %s\n", s->sub_b);
	buf = ft_substr(s->s, ft_strlen(s->sub_b) + 1, *i);
// printf("STRING expand = %s\n", s->sub_m);
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
// printf("STRING AFTER = %s\n", s->sub_a);
	// buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, buf);
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

void	expand_dollar(t_data *data, t_substr *s, size_t *i, size_t index)
{
	char	*buf;

	*i = *i + 1;
	if (s->s[*i] == '?')
	{
		question_mark(data, s, i, index);
		return ;//add function with signals later
	}
	else if (ft_isdigit(s->s[*i]) == 1)
	{
		number_xpd(data, s, i, index);
		return;
	}
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i);
	buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, buf);
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

char	*get_var(t_data *data, char *s)
{
	char	*var;
	char	*ptr;
	size_t	i;
	size_t	k;

	k = -1;
	ptr = ft_substr(s, 1, ft_strlen(s) - 1);
	var = ft_strdup("");
	if (var == NULL)
		exit_error(data);
	while (data->envp[++k])
	{
		i = 0;
		while (data->envp[k][i] != '=')
			i++;
		if (ft_strncmp(data->envp[k], ptr, ft_strlen(ptr)) == 0 && \
			ft_strlen(ptr) == i)
		{
			free(var);
			var = ft_substr(data->envp[k], i + 1, (ft_strlen(data->envp[k])));
			if (var == NULL)
				exit_error(data);
			break ;
		}
	}
	return (free(ptr), free(s), var);
}

char	*join_all(char *s, char *b, char *e, char *a)
{
	free(s);
	s = NULL;
	if (b != NULL && e != NULL)
		s = ft_strjoin_free(b, e);//ft_strjoin_free

	else if (b == NULL && e != NULL)
	{
		s = ft_strdup(e);
		free(e);
	}

	else if (b != NULL && e == NULL)
	{
		s = ft_strdup(b);
		free(b);
	}

	if (a != NULL)
		s = ft_strjoin_free(s, a);//ft_strjoin_free


	// if (e != NULL)
	// 	free(e);
	return (s);
}

// void	free_struct_expand(t_substr *str) //appara;ent useless
// {
// 	if (str->before != NULL)
// 		free(str->before);
// 	if (str->middle != NULL)
// 		free(str->middle);
// 	if (str->after != NULL)
// 		free(str->after);
// 	if (str->sub_b != NULL)
// 		free(str->sub_b);
// 	if (str->sub_m != NULL)
// 		free(str->sub_m);
// 	if (str->sub_a != NULL)
// 		free(str->sub_a);
// }
