/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:28:23 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 11:13:41 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	data_initialize(t_data *data, char **envp)
{//bzero sur struct met tout a 0 A changer
	char		*user;
	t_heredoc	doc;

	data->cmd = NULL;
	data->env = NULL;
	data->envp = get_envp(data, envp);
	data->lexer = NULL;
	data->str = NULL;
	data->prompt = NULL;
	doc.LIMITER = NULL;
	doc.heredoc = 0;
	doc.hd_count = 0;
	data->hd = &doc;
	data->fdin = 0;
	data->fdout = 0;
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

static t_env	*new_env_node(char *str)
{
	t_env	*new;
	char	*pos;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->prev = NULL;
	new->next = NULL;
	pos = ft_strchr(str, '=');
	if (pos)
	{
		new->var_name = ft_strndup(str, (size_t)pos - (size_t)str);
		new->var_value = ft_strdup(pos + 1);
		if (!new->var_name || !new->var_value)
			return (0);
	}
	else
	{
		new->var_name = ft_strdup(str);
		new->var_value = NULL;
		if (!new->var_name)
			return (0);
	}
	return (new);
}

int	add_env_node(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*new;

	new = new_env_node(str);
	if (!new)
		return (0);
	if (!*env)
	{
		*env = new;
		return (1);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (1);
}

char	**get_envp(t_data *data, char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	// if (!new_envp)
	// 	;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "_=", 2) == 0)
		{
			new_envp[i] = ft_strdup("_=/usr/bin/env");
			add_env_node(&data->env, new_envp[i]);
		}
		else if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			new_envp[i] = get_shlvl(envp[i]);
			add_env_node(&data->env, new_envp[i]);
		}
		else if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			new_envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			add_env_node(&data->env, new_envp[i]);
		}
		else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			new_envp[i] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
			add_env_node(&data->env, new_envp[i]);
		}
		else
		{
			new_envp[i] = ft_strdup(envp[i]);
			if (!new_envp || !add_env_node(&data->env, envp[i]))
				return (NULL);
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}
