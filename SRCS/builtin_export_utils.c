/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 10:59:43 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_list_size(t_env *env)
{
	int	len;

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
