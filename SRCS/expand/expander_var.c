/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:50:17 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/13 14:11:11 by rrebois          ###   ########lyon.fr   */
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
			expand_error(data, s, "minishell: malloc_error");
	}
	while (ft_isalnum(s->s[*i]) == 1)
		*i = *i + 1;
	s->sub_a = ft_substr_check(s->s, *i + 1, ft_strlen(s->s) - *i, &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error");
	s->sub_m = ft_itoa(g_status);
	if (s->sub_m == NULL)
		expand_error(data, s, "minishell: malloc error");
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

static void	sub_number_xpd(t_data *data, t_substr *s, size_t *i, int *err)
{
	if (*i > 1)
	{
		s->sub_b = ft_substr_check(s->s, 0, *i - 1, err);
		if (*err > 0)
			expand_error(data, s, "minishell: malloc_error");
	}
	data->buf = ft_substr_check(s->s, ft_strlen(s->sub_b) + 1, *i, err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc_error: ");
	s->sub_a = ft_substr_check(s->s, *i + 1, ft_strlen(s->s) - *i, err);
	if (*err > 0)
		expand_error(data, s, "minishell: malloc error");
}

void	number_xpd(t_data *data, t_substr *s, size_t *i, size_t index)
{
	int		err;

	err = 0;
	sub_number_xpd(data, s, i, &err);
	s->sub_m = get_var(data, data->buf, &err);
	if (err > 0)
		expand_error(data, s, "minishell: malloc error: ");
	if (check_space_expand(data, s, index) == 1)
		return ;
	*i = ft_strlen(s->sub_b) + ft_strlen(s->sub_m);
	s->s = join_all_sub(data, s->s, s);
}

static char	*envp_loop(t_data *data, char *var, char *ptr, int *err)
{
	size_t	i;
	size_t	k;

	k = -1;
	while (data->envp[++k])
	{
		i = 0;
		while (data->envp[k][i] != '=')
			i++;
		if (ft_strncmp(data->envp[k], ptr, ft_strlen(ptr)) == 0 && \
			ft_strlen(ptr) == i)
		{
			free(var);
			var = ft_substr_check(data->envp[k], i + 1, \
									(ft_strlen(data->envp[k])), err);
			if (*err > 0)
				return (NULL);
			break ;
		}
	}
	return (var);
}

char	*get_var(t_data *data, char *s, int *err)
{
	char	*var;
	char	*ptr;

	ptr = ft_substr_check(s, 1, ft_strlen(s) - 1, err);
	if (*err > 0)
		return (free(s), NULL);
	var = ft_strdup("");
	if (var == NULL)
	{
		*err = 1;
		return (free(ptr), free(s), NULL);
	}
	var = envp_loop(data, var, ptr, err);
	if (var == NULL)
	{
		var = malloc(sizeof(char *));
		var[0] = '\0';
	}
	if (*err > 0)
		return (free(ptr), free(s), NULL);
	return (free(ptr), free(s), var);
}
