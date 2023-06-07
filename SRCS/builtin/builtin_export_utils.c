/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/07 14:09:29 by tgellon          ###   ########lyon.fr   */
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

	if (ft_strncmp(var->var_name, cmd, i) == 0 && ft_strchr(cmd, '='))
	{
		pos = ft_strchr(cmd, '=');
		free(var->var_name);
		free(var->var_value);
		var->var_value = ft_strdup(pos + 1);
		var->var_name = ft_strndup(cmd, i);
		if (!var->var_value || !var->var_name)
			exit_error(data, "minishell: malloc error: ");
		return (1);
	}
	else if (ft_strncmp(var->var_name, cmd, i) == 0)
		return (1);
	return (0);
}

int	envp_replacement(t_data *data, char **var, char *cmd)
{
	free(*var);
	*var = ft_strdup(cmd);
	if (!*var)
		exit_error(data, "minishell: malloc error: ");
	return (1);
}

char	**export_var_only(t_data *data, char *cmd)
{
	int		j;
	int		n;
	char	**new_envp;

	n = 0;
	j = -1;
	while (data->envp[n])
		n++;
	new_envp = malloc(sizeof(char *) * (n + 2));
	if (!new_envp)
		exit_error(data, "minishell: malloc error: ");
	while (data->envp[++j])
	{
		new_envp[j] = ft_strdup(data->envp[j]);
		free(data->envp[j]);
	}
	free(data->envp);
	new_envp[n] = ft_strdup(cmd);
	new_envp[n + 1] = 0;
	if (!new_envp[n])
		exit_error(data, "minishell: malloc error: ");
	return (new_envp);
}


int	existing_var(t_data *data, char *cmd, int i)
{
	t_env	*tmp;
	int		j;
	int		export;

	tmp = data->env;
	export = 0;
	while (tmp)
	{
		if (env_struct_replacement(data, tmp, cmd, i) == 1)
		{
			export = 1;
			break ;
		}
		else
			tmp = tmp->next;
	}
	j = -1;
	while (data->envp[++j])
	{
		if (ft_strncmp(data->envp[j], cmd, i) == 0 && ft_strchr(cmd, '=') \
			&& export == 1)
		{
			envp_replacement(data, &data->envp[j], cmd);
			export += 1;
			break ;
		}
		else if (export == 1 && ft_strchr(cmd, '='))
		{
			data->envp = export_var_only(data, cmd);
			break ;
		}
	}
	return (export);
}
