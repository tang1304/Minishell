/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:08:20 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/19 14:32:12 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_shlvl(char *str)
{
	char	*newlvl;
	char	*pos;
	char	*itoa;
	int		lvl;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	pos = ft_strchr(str, '=');
	lvl = ft_atoi(pos + 1);
	itoa = ft_itoa(lvl + 1);
	// if (!itoa)
	// 	;
	newlvl = ft_strjoin("SHLVL=", itoa);
	free(itoa);
	// if (!newlvl)
	// 	;
	return (newlvl);
}

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
			tmp->var_value = ft_strdup(old_env);
			if (!tmp->var_value)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static t_env	*new_env_node(char *str)
{
	t_env	*new;
	char	*pos;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->prev = NULL;
	new->next = NULL;
	pos = ft_strchr(str, '=');
	if (pos)
	{
		new->var_name = ft_strndup(str, (size_t)pos - (size_t)str);
		new->var_value = ft_strdup(pos + 1);
		if (!new->var_name || !new->var_value)
			return (0);
	}
	else
	{
		new->var_name = ft_strdup(str);
		new->var_value = ft_strdup("");
		if (!new->var_name)
			return (0);
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
