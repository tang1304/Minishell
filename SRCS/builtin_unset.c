/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:54:14 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/25 11:33:40 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	unset_var(t_data *data, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (data->envp[j])
		j++;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], str, ft_strlen(str) - 1) == 0)
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

static t_env	*remove_node(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	if (tmp->next == NULL && tmp->prev == NULL)
		*envp = NULL;
	else if (tmp->prev == NULL)
	{
		*envp = tmp->next;
		tmp->next->prev = NULL;
	}
	else if (tmp->next == NULL)
		tmp->prev->next = NULL;
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	if (tmp->var_name)
		free(tmp->var_name);
	if (tmp->var_value)
		free(tmp->var_value);
	free(tmp);
	return (*envp);
}

int	ft_unset(t_data *data, char **cmd)
{
	t_env	*lst;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (!ft_isalnum(cmd[i][0]) || ft_isdigit(cmd[i][0]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			continue ;
		}
		lst = data->env;
		while (lst)
		{
			if (ft_strncmp(cmd[i], lst->var_name, \
				ft_strlen(lst->var_name) - 1) == 0)
			{
				unset_var(data, lst->var_name);
				lst = remove_node(&lst);
			}
			lst = lst->next;
		}
	}
	return (1);
}
