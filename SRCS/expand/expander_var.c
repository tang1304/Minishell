/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 09:12:01 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	question_mark(t_data *data, t_substr *s, size_t *i, size_t index)
{
	int	err;

	err = 0;
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, &err);
		if (err > 0)
			exit_error(data, "minishell: malloc_error: ");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr_check(s->s, *i + 1, ft_strlen(s->s) - *i, &err);
	if (err > 0)
		exit_error(data, "minishell: malloc error :"); // mettre expand_error;
	s->sub_m = ft_itoa(g_status);
	if (s->sub_m == NULL)
		exit_error(data, "minishell: malloc error :");// mettre expand_error;
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	number_xpd(t_data *data, t_substr *s, size_t *i, size_t index)
{
	char	*buf;

	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	buf = ft_substr(s->s, ft_strlen(s->sub_b) + 1, *i);
	s->sub_a = ft_substr(s->s, *i + 1, ft_strlen(s->s) - *i);
	s->sub_m = get_var(data, buf, 0);
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

void	expand_dollar(t_data *data, t_substr *s, size_t *i, size_t index)
{
	char	*buf;

	*i = *i + 1;
	if (s->s[*i] == '?')
	{
		question_mark(data, s, i, index);
		return ;
	}
	else if (ft_isdigit(s->s[*i]) == 1)
	{
		number_xpd(data, s, i, index);
		return ;
	}
	if (*i > 1)
		s->sub_b = ft_substr(s->s, 0, *i - 1);
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr(s->s, *i, ft_strlen(s->s) - *i + 1);
	buf = ft_substr(s->s, ft_strlen(s->sub_b), *i - (ft_strlen(s->sub_b)));
	s->sub_m = get_var(data, buf, 0);
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

char	*get_var(t_data *data, char *s, size_t i)
{
	char	*var;
	char	*ptr;
	size_t	k;

	k = -1;
	ptr = ft_substr(s, 1, ft_strlen(s) - 1);
	var = ft_strdup("");
	if (var == NULL)
		exit_error(data, "minishell: malloc error 22: ");
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
				exit_error(data, "minishell: malloc error 23: ");
			break ;
		}
	}
	return (free(ptr), free(s), var);
}
