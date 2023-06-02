/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/02 10:40:13 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_list_size(t_env *env)
{
	int		len;

	len = 0;
	while (env != NULL)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static int	env_struct_replacement(t_data *data, t_env *var, char *cmd, int i)
{
	char	*pos;

	if (ft_strncmp(var->var_name, cmd, i) == 0)
	{
		pos = ft_strchr(cmd, '=');
		free(var->var_name);
		if (pos)
		{
			free(var->var_value);
			var->var_value = ft_strdup(pos + 1);
		}
		else
			var->var_value = ft_strdup("");
		var->var_name = ft_strndup(cmd, i);
		if (!var->var_value)
			exit_error(data);
		return (1);
	}
	return (0);
}

int	envp_replacement(char **var, char *cmd)
{
	free(*var);
	*var = ft_strdup(cmd);
	if (!*var)
		return (0);
	return (1);
}

static void	remove_from_env(t_data *data, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (data->envp[j])
		j++;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], str, ft_strlen(str)) == 0)
		{
			free(data->envp[i]);
			while (i < j - 1)
			{
				data->envp[i] = data->envp[i + 1];
				i++;
			}
			data->envp[i] = NULL;
			break ;
		}
	}
}

int	existing_var(t_data *data, char *cmd, int i)
{
	t_env	*tmp;
	int		j;

	tmp = data->env;
	while (tmp)
	{
		if (env_struct_replacement(data, tmp, cmd, i) == 1)
			break ;
		else
			tmp = tmp->next;
	}
	j = -1;
	while (data->envp[++j])
	{
		if (ft_strncmp(data->envp[j], cmd, i) == 0)
		{
			if (ft_strchr(cmd, '='))
				envp_replacement(&data->envp[j], cmd);
			else
				remove_from_env(data, cmd);
			return (1);
		}
	}
	return (0);
}
