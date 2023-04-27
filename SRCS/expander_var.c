/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 17:21:40 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	expand_dollar(t_data *data, t_substr *s, size_t *i)
{
	*i = *i + 1;
	if (s->s[*i] == '?')
		return ; //add function with signals later
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i);
	s->sub_m = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, s->sub_m);
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all(s->s, s->sub_b, s->sub_m, s->sub_a);
}

char	*get_var(t_data *data, char *s)
{
	char	*var;
	size_t	i;
	size_t	k;

	k = 0;
	s = ft_substr(s, 1, ft_strlen(s) - 1);
	var = ft_strdup("");
	// if (var == NULL)
	// 	return (NULL);
	while (data->envp[k])
	{
		i = 0;
		while (data->envp[k][i] != '=')
			i++;
		if (ft_strncmp(data->envp[k], s, ft_strlen(s)) == 0 && ft_strlen(s) == i)
		{
			free(var);
			var = ft_substr(data->envp[k], i + 1, (ft_strlen(*data->envp)));
			// if (var == NULL)
			// 	return (NULL);
			break ;
		}
		k++;
	}
	return (var);
}

char	*join_all(char *s, char *b, char *e, char *a)
{
	free(s);
	s = NULL;
	if (b != NULL && e != NULL)
		s = ft_strjoin_free(b, e);
	else if (b == NULL && e != NULL)
		s = ft_strdup(e);
	else if (b != NULL && e == NULL)
		s = ft_strdup(b);
	if (a != NULL)
		s = ft_strjoin_free(s, a);
	return (s);
}

// void	free_struct_expand(t_substr *str) appara;ent useless
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
