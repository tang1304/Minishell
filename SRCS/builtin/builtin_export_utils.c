/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/19 16:00:36 by tgellon          ###   ########lyon.fr   */
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

void	ft_list_sort(t_env **env, int size)
{
	void	*tmp_name;
	void	*tmp_value;
	t_env	*current;
	int		i;
	int		j;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		current = *env;
		while (++j < size - 1 - i)
		{
			if (ft_strcmp(current->var_name, current->next->var_name) > 0)
			{
				tmp_name = current->var_name;
				tmp_value = current->var_value;
				current->var_name = current->next->var_name;
				current->var_value = current->next->var_value;
				current->next->var_name = tmp_name;
				current->next->var_value = tmp_value;
			}
			current = current->next;
		}
	}
}

static int	env_struct_replacement(t_env *var, char *cmd, int i)
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
		// if (!tmp->var_value)
		// 	return (0);
		return (1);
	}
	return (0);
}

// static int	envp_replacement(char **var, char *cmd)
// {
// 	free(*var);
// 	*var = ft_strdup(cmd);
// 	if (!*var)
// 		return (0);
// 	return (1);
// }

int	existing_var(t_data *data, char *cmd, int i)
{
	t_env	*tmp;
	// int		j;

	tmp = data->env;
	while (tmp)
	{
		if (env_struct_replacement(tmp, cmd, i) == 1)
		{
			return (1);
			// break ;
		}
		else
			tmp = tmp->next;
	}
	// j = -1;
	// while (data->envp[++j])
	// {
	// 	if (ft_strncmp(data->envp[j], cmd, i) == 0)
	// 	{
	// 		envp_replacement(&data->envp[j], cmd);
	// 		printf("Envp replaced\n");
	// 		return (1) ;
	// 	}
	// }
	return (0);
}
