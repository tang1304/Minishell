/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:28:23 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/25 09:50:14 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	data_initialize(t_data *data, char **envp)
{
	char	*user;

	data->cmd = NULL;
	data->envp = get_envp(envp);
	data->lexer = NULL;
	data->str = NULL;
	data->prompt = NULL;
	data->LIMITER = NULL;
	data->heredoc = 0;
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

char	**get_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp)
			return (NULL);
	}
	new_envp[i] = NULL;
	return (new_envp);
}
