/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 10:34:48 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// export name=value
// '(' ou ')' dans cmd[1] : bash: syntax error near unexpected token `('
// si name commence par un digit, ou contient un ':' ';' '?' '@'
// si value contient un ';' '(' ou ')'
//export name -> name n'est pas dans env, mais présent dans export

int	ft_print_export(t_env **env)
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
		printf("declare -x ");
		printf("%s\"", tmp->var_name);
		printf("%s\"\n", tmp->var_value);
		tmp = tmp->next;
		i++;
	}
	return (1);
}

void	ft_export(t_data *data, char **cmd)
{
	int	i;

	if (!cmd[1] || cmd[1][0] == '\0')
	{
		ft_print_export(&data->env);
		return ;
	}
	i = 0;
	if (cmd[2])
	{
		while (cmd[++i])
			printf("minishell: export: `%s' : not a valid identifier\n", cmd[i]);
		return ;
	}
	if (!ft_isalnum(cmd[1][0]) || ft_isdigit(cmd[1][0]))
		printf("minishell: export: `%s' : not a valid identifier\n", cmd[1]);
	while (cmd[1][++i] != '=' || cmd[1][++i])
	{
		if (cmd[1][i] == '(' || cmd[1][i] == ')')
			printf("minishell: syntax error near unexpected token `%c'\n", cmd[1][i]);
		if (cmd[1][i] != '_' || !ft_isalnum(cmd[1][i]))
			printf("minishell: export: `%s' : not a valid identifier\n", cmd[1]);
	}
	if (cmd[1][i] == '\0')
		return ;
	// while (cmd[1][++i])
	// {
	// 	if (cmd[1][i])
	// 		;
	// 	if (cmd[1][i] == ';' || cmd[1][i] == '(' || cmd[1][i] == ')')
	// 		;
	// }
}
