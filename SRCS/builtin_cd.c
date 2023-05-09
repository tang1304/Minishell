/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/09 13:22:52 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*search_env(t_data *data, char *env)
{
	t_env	*tmp;
	size_t	size;
	size_t	i;

	tmp = data->env;
	// printf("%s\n", tmp->);
	size = ft_list_size(tmp);
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(tmp->var_name, env, ft_strlen(env)) == 0)
			return (tmp->var_value);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

int	replace_env(t_data *data, char *env, char *old_env)
{
	t_env	*tmp;
	size_t	size;
	size_t	i;

	i = 0;
	tmp = data->env;
	size = ft_list_size(tmp);
	while (i < size)
	{
		if (ft_strncmp(tmp->var_name, env, ft_strlen(env)) == 0)
		{
			free(tmp->var_value);
			tmp->var_value = ft_strdup(old_env);
			// if (!tmp->var_value)
			// 	;
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static char	*ddot_handle(t_data *data)
{
	t_env	*tmp;
	char	*new_path;
	char	*pos;
	size_t	len;
	size_t	i;

	tmp = data->env;
	len = ft_list_size(tmp);
	i = -1;
	while (++i < len)
	{
		if (ft_strncmp(tmp->var_name, "PWD=", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	pos = ft_strrchr(tmp->var_value, '/');
	new_path = ft_strndup(tmp->var_value, (size_t)pos - \
							(size_t)tmp->var_value - 1);
	// if (!new_path)
	// 	return (0);
	chdir(new_path);
	return (new_path);
}

static int	cd_home(t_data *data)
{
	char	*home;
	char	*current;

	home = search_env(data, "HOME=");
	if (home == NULL)
		return (printf("HOME not set"), 0);
	printf("\nhome: %s\n", home);
	chdir(home);
	current = getcwd(NULL, 0);
	if (current != NULL)
	{
		replace_env(data, "OLDPWD=", search_env(data, "PWD="));
		replace_env(data, "PWD=", current);
		print_export(&data->env);
		return (1);
	}
	return (perror("getcwd: "), 0);
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*current;

	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0' \
		|| (cmd[1][0] == '~' && !cmd[1][1])))//OK
	{
		if (!cd_home(data))
			return (printf("HOME not set"), 0);
		return (1);
	}
	if (cmd[2])// OK
		return (printf("minishell: cd: too many arguments\n"), 0);
	if (ft_strnstr(cmd[1], "..", 2) && ft_strlen(cmd[1]) == 2)//OK
	{
		if (!ddot_handle(data))
			return (0);
	}
	else if (ft_strnstr(cmd[1], ".", 1) && ft_strlen(cmd[1]) == 1)//OK
		return (1);
	else if (chdir(cmd[1]) == -1)
	{
		return (perror("chdir: "), 0);
	current = getcwd(NULL, 0);
	if (current != NULL)//fonctionne pour dossier enfant
	{
		printf("3\n");
		replace_env(data, "OLDPWD=", search_env(data, "PWD="));
		replace_env(data, "PWD=", current);
		print_export(&data->env);
		return (1);
	}
	return (perror("getcwd: "), 0);
}
