/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/30 09:07:27 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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

int	print_export(t_env **env)
{
	t_env	*tmp;
	int		i;
	int		size;

	tmp = *env;
	size = ft_list_size(tmp);
	ft_list_sort(env, size);
	i = -1;
	while (++i < size)
	{
		if (tmp->var_name[0] == '_' && tmp->var_name[1] == '=')
		{
			tmp = tmp->next;
			continue ;
		}
		printf("declare -x ");
		printf("%s", tmp->var_name);
		if (tmp->var_value && ft_strchr(tmp->var_name, '='))
			printf("\"%s\"\n", tmp->var_value);
		else
			printf("\n");
		tmp = tmp->next;
	}
	return (1);
}

static int	name_check(char *str)
{
	int	i;

	i = 0;
	if ((!ft_isalnum(str[0]) && str[0] != '_') || ft_isdigit(str[0]))
	{
		printf("minishell: export: `%s' : not a valid identifier\n", str);
		return (-1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			continue ;
		else
		{
			printf("minishell: export: `%s' : not a valid identifier\n", str);
			return (-1);
		}
	}
	return (i);
}

static char	**export_var(t_data *data, char *cmd)
{
	int		j;
	int		n;
	char	**new_envp;

	n = 0;
	j = -1;
	while (data->envp[n])
		n++;
	new_envp = malloc(sizeof(char *) * (n + 2));
	if (!new_envp || !add_env_node(&data->env, cmd))
		return (NULL);
	while (data->envp[++j])
	{
		new_envp[j] = ft_strdup(data->envp[j]);
		free(data->envp[j]);
	}
	free(data->envp);
	new_envp[n] = ft_strdup(cmd);
	new_envp[n + 1] = '\0';
	if (!new_envp[n])
		return (NULL);
	return (new_envp);
}

int	ft_export(t_data *data, char **cmd)
{
	int	i;
	int	j;

	if (!cmd[1] || cmd[1][0] == '\0')
		return (print_export(&data->env), 1);
	j = 0;
	while (cmd[++j])
	{
		i = name_check(cmd[j]);
		if (i == -1)
			continue ;
		if (existing_var(data, cmd[j], i))
			return (1);
		if (cmd[j][i] == '\0')
		{
			if (!add_env_node(&data->env, cmd[j]))
				return (-1);
			continue ;
		}
		data->envp = export_var(data, cmd[j]);
		if (!data->envp)
			return (-1);
	}
	return (1);
}
