/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 14:21:56 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	expand_dollar(t_data *data, t_substr *s, size_t *i) //func too long
{
	*i = *i + 1;
	if (s->s[*i] == '?')
		return ; //add function with signals later
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;

if (s->sub_b != NULL)
	printf("\n\n\nbef = %s c = %d\n", s->sub_b, s->sub_b[ft_strlen(s->sub_b) - 1]);
// printf("%ld vs %ld\n", *i, ft_strlen(s->s));
// printf("char stopped: %d=%c\n", s->middle[j], s->middle[j]);
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i);
printf("aft = %s c = %c %d\n", s->sub_a, s->sub_a[ft_strlen(s->sub_a) - 1], s->sub_a[ft_strlen(s->sub_a) - 1]);
	s->sub_m = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
printf("exp = %s c = %c %d\n\n\n", s->sub_m, s->sub_m[ft_strlen(s->sub_m) - 1], s->sub_a[ft_strlen(s->sub_a) - 1]);
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
printf("expand: %s\n", s);
	var = ft_strdup("");
	// if (var == NULL)
	// 	return (NULL);
	while (data->envp[k])
	{
printf("data->env[%ld] = %s\n", k, data->envp[k]);
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
		s = e;
	else if (b != NULL && e == NULL)
		s = b;
	if (a != NULL)
		s = ft_strjoin_free(s, a);
	return (s);
}
