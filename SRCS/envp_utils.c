/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:08:20 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/08 12:10:46 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_shlvl(t_data *data, char *str)
{
	char	*newlvl;
	char	*pos;
	char	*itoa;
	int		lvl;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	pos = ft_strchr(str, '=');
	lvl = ft_atoi(pos + 1);
	itoa = ft_itoa(lvl + 1);
	if (!itoa)
		exit_error(data, "minishell: malloc error: ");
	newlvl = ft_strjoin("SHLVL=", itoa);
	free(itoa);
	if (!newlvl)
		exit_error(data, "minishell: malloc error: ");
	return (newlvl);
}
