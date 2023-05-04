/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/04 10:12:13 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// export name=value

static int	print_export(t_env **env)
{
	t_env	*tmp;
	int		i;
	int		size;

	tmp = *env;
	size = ft_list_size(tmp);
	ft_list_sort(env, size);
	i = 0;
	while (i < size)
	{
		if (tmp->var_name[0] == '_' && tmp->var_name[1] == '=')
		{
			tmp = tmp->next;
			i++;
			continue ;
		}
		printf("declare -x ");
		printf("%s\"", tmp->var_name);
		printf("%s\"\n", tmp->var_value);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

static int	name_check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalnum(str[0]) || ft_isdigit(str[0]))
	{
		printf("minishell: export: `%s' : not a valid identifier\n", str);
		return (-1);
	}
	while (str[++i] != '=' || str[++i])
	{
		if (str[i] != '_' || !ft_isalnum(str[i]))
		{
			printf("minishell: export: `%s' : not a valid identifier\n", str);
			return (-1);
		}
	}
	return (i);
}

static char	**export_var(t_data *data, char *cmd)
{
	int		i;
	int		n;
	char	**new_envp;

	add_env_node(&data->env, cmd);
	i = -1;
	n = 0;
	while (data->envp[n])
		n++;
	new_envp = malloc(sizeof(char *) * (n + 1));
	// if (!new_envp)
	// 	;
	ft_memcpy(new_envp, data->envp, sizeof(char *));
	while (data->envp[i])
		free(data->envp[i]);
	free(data->envp);
	new_envp[n] = ft_strdup(cmd);
	// if (!new_envp[n])
	// 	;
	return (new_envp);
}

void	ft_export(t_data *data, char **cmd)
{
	int	i;
	int	j;

	if (!cmd[1] || cmd[1][0] == '\0')
	{
		print_export(&data->env);
		return ;
	}
	j = -1;
	while (cmd[++j])
	{
		i = name_check(cmd[j]);
		if (i == -1)
			continue ;
		if (cmd[j][i] == '\0')
		{
			add_env_node(&data->env, cmd[j]);
			continue ;
		}
		else
		{
			data->envp = export_var(data, cmd[j]);
			// if (!data->envp)
			// 	;
		}
	}
}
