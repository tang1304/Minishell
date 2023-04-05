/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:07:42 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/04 15:16:38 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// export name=value
// '(' ou ')' dans cmd[1] : bash: syntax error near unexpected token `('
// si name commence par un digit, ou contient un ':' ';' '?' '@'
void	ft_export(t_data *data, char **cmd)
{
	int	i;

	if (!cmd[1] || cmd[1][0] == '\0')
	{
		ft_env(data);
		return ;
	}
	i = 0;
	if (cmd[2])
	{
		while (cmd[++i])
			printf("minishell: export: `%s' : not a valid identifier\n", cmd[i]);
		return ;
	}
	if (ft_isspace(cmd[1][0]) || cmd[1][0] == '=' || ft_isdigit(cmd[1][0]))
		printf("minishell: export: `%s' : not a valid identifier\n", cmd[1]);
	while (cmd[1][++i] != '=')
	{
		if (cmd[1][i] == '(' || cmd[1][i] == ')')
			printf("minishell: syntax error near unexpected token `%c'\n", cmd[1][i]);
		if (ft_isspace(cmd[1][i]) || (cmd[1][i] >= 33 && cmd[1][i] <= 47))
			printf("minishell: export: `%s' : not a valid identifier\n", cmd[1]);
	}
}
