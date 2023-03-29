/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:28:23 by rrebois           #+#    #+#             */
/*   Updated: 2023/03/29 12:23:19 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	data_initialize(t_data *data, char **envp)
{
	char	*user;

	data->envp = envp;
	data->lexer = NULL;
	data->lexer = NULL;
	data->str = NULL;
	data->prompt = NULL;
	user = getenv("USER");
	if (user != NULL)
		data->prompt = ft_strjoin(user, "@minishell:");
	else
		data->prompt = ft_strjoin("root", "@minishell:");
//surement leaks de ft_strjoin, faire un ft_strjoin avec double free a la fin
	update_pwd(data, "~");
}

void	update_pwd(t_data *data, char *s)
{
	data->oldpwd = data->pwd;
	data->pwd = s;
	data->prompt_pwd = data->pwd;
	prompt_loop(data);
}
