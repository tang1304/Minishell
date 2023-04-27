/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:08:20 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/27 16:55:14 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*get_shlvl(char *str)
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
	newlvl = ft_strjoin("SHLVL=", itoa);
	free(itoa);
	// if (!newlvl)
	// 	;
	return (newlvl);
}
