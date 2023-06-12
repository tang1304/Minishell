/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:11:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/12 12:01:30 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	iterate_pp_envp(t_data *data, char *cmd, int i, int export)
{
	int	j;

	j = -1;
	while (data->envp[++j])
	{
		if (ft_strncmp(data->envp[j], cmd, i) == 0 && ft_strchr(cmd, '=') \
			&& export == 1)
		{
			envp_replacement(data, &data->envp[j], cmd);
			export += 1;
			return ;
		}
	}
	if (export == 1 && ft_strchr(cmd, '='))
	{
		data->envp = export_var_only(data, cmd);
		return ;
	}
}
