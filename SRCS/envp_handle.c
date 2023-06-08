/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:08:20 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/08 15:13:31 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*search_env(t_data *data, char *env)
{
	t_env	*tmp;
	size_t	size;
	size_t	i;

	tmp = data->env;
	size = ft_list_size(tmp);
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(tmp->var_name, env, ft_strlen(env)) == 0)
			return (tmp->var_value);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int	replace_env(t_data *data, char *env, char *old_env)
{
	t_env	*tmp;
	size_t	size;
	size_t	i;

	i = 0;
	tmp = data->env;
	size = ft_list_size(tmp);
	while (i < size)
	{
		if (ft_strncmp(tmp->var_name, env, ft_strlen(env)) == 0)
		{
			free(tmp->var_value);
			if (old_env == NULL)
				tmp->var_value = ft_strdup("");
			else
				tmp->var_value = ft_strdup(old_env);
			if (!tmp->var_value)
				exit_error(data, "minishell: malloc error: ");
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static int	env_var_no_value(t_env *new, char *str)
{
	new->var_name = ft_strdup(str);
	if (!new->var_name)
		return (free(new), 0);
	new->var_value = ft_strdup("");
	if (!new->var_value)
		return (free(new->var_name), free(new), 0);
	return (1);
}

static t_env	*new_env_node(char *str)
{
	t_env	*new;
	char	*pos;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	pos = ft_strchr(str, '=');
	if (pos)
	{
		new->var_name = ft_strndup(str, (size_t)pos - (size_t)str);
		if (!new->var_name)
			return (free(new), NULL);
		new->var_value = ft_strdup(pos + 1);
		if (!new->var_value)
			return (free(new->var_name), free(new), NULL);
	}
	else
	{
		if (!env_var_no_value(new, str))
			return (NULL);
	}
	return (new);
}

int	add_env_node(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	new = new_env_node(str);
	if (!new)
		return (0);
	if (!*env)
	{
		*env = new;
		return (1);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (1);
}
