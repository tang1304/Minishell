/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/05/03 15:09:45 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// export name=value
// si name commence par un digit, ou contient un ':' ';' '?' '@'
// si value contient un ';' '(' ou ')'
//export name -> name n'est pas dans env, mais présent dans export

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

int	name_check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalnum(str[0]) || ft_isdigit(str[0]))
	{
		printf("minishell: export: `%s' : not a valid identifier\n", str[1]);
		return (0);
	}
	while (str[++i] != '=' || str[++i])
	{
		if (str[i] != '_' || !ft_isalnum(str[i]))
		{
			printf("minishell: export: `%s' : not a valid identifier\n", str);
			return (0);
		}
	}
	return (1);
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
		if (!name_check(cmd[j]))
			continue ;
		if (cmd[j][i] == '\0')
			continue ;
		while (cmd[1][++i])
		{
			if (cmd[1][i])
				;
			if (cmd[1][i] == ';')
				;
		}
	}
}
