/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:28:23 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/05 09:01:47 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*update_pwd(t_data *data)
{
	char	*prompt;

	if (search_env(data, "PWD") == NULL)
	{
		data->prompt_pwd = getcwd(NULL, 0);
		if (!data->prompt_pwd)
		{
			perror("minishell: pwd: ");
			exit_error(data);
		}
		prompt = ft_strjoin_free_s2(data->prompt, data->prompt_pwd);
	}
	else
	{
		data->prompt_pwd = search_env(data, "PWD");
		prompt = ft_strjoin(data->prompt, data->prompt_pwd);
	}
	prompt = ft_strjoin_gnl(prompt, "$ ");
	return (prompt);
}

static char	*envp_handle(char *str)
{
	char	*new_envp;

	if (ft_strncmp(str, "_=", 2) == 0)
		new_envp = ft_strdup("_=/usr/bin/env");
	else if (ft_strncmp(str, "SHLVL=", 6) == 0)
		new_envp = get_shlvl(str);
	else if (ft_strncmp(str, "PWD=", 4) == 0)
		new_envp = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
	else if (ft_strncmp(str, "OLDPWD=", 7) == 0)
		new_envp = ft_strjoin_free_s2("OLDPWD=", getcwd(NULL, 0));
	else
		new_envp = ft_strdup(str);
	return (new_envp);
}

char	**env_i_handle(t_data *data)
{
	char	**envp;
	int		i;

	i = -1;
	envp = (char **)malloc(sizeof(char *) * 5);
	envp = NULL;
	if (!envp) // test
		return (NULL);
	while (++i < 4)
	{
		if (i == 0)
			envp[i] = ft_strjoin_free_s2("PWD=", getcwd(NULL, 0));
		else if (i == 1)
			envp[1] = ft_strdup("SHLVL=1");
		else if (i == 2)
			envp[2] = ft_strdup("_=/usr/bin/env");
		else if (i == 3)
			envp[3] = ft_strjoin_free_s2("OLDPWD=", getcwd(NULL, 0));
		if (!envp[i] || !add_env_node(&data->env, envp[i]))
			return (NULL);
	}
	envp[4] = NULL;
	return (envp);
}

char	**get_envp(t_data *data, char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		exit_error(data);
	i = -1;
	while (envp[++i])
	{
		new_envp[i] = envp_handle(envp[i]);
		if (!new_envp || !add_env_node(&data->env, new_envp[i]))
			return (NULL);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	data_initialize(t_data *data, char **envp)
{
	char		*user;
	t_heredoc	doc;

	g_status = 0;
	ft_bzero(&doc, sizeof(t_heredoc));
	if (!envp[0])
		data->envp = env_i_handle(data);
	else
		data->envp = get_envp(data, envp);
	data->hd = &doc;
	user = getenv("USER");
	if (user != NULL)
		data->prompt = ft_strjoin(user, "@minishell:");
	else
		data->prompt = ft_strjoin("root", "@minishell:");
	prompt_loop(data);
}
