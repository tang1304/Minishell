/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:08:20 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/09 13:38:35 by tgellon          ###   ########lyon.fr   */
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
			// if (!tmp->var_value)
			// 	;
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}
