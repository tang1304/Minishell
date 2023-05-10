/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/09 14:09:43 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// static char	*ddot_handle(t_data *data)
// {
// 	t_env	*tmp;
// 	char	*new_path;
// 	char	*pos;
// 	size_t	len;
// 	size_t	i;

// 	tmp = data->env;
// 	len = ft_list_size(tmp);
// 	i = -1;
// 	while (++i < len)
// 	{
// 		if (ft_strncmp(tmp->var_name, "PWD=", 4) == 0)
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	pos = ft_strrchr(tmp->var_value, '/');
// 	new_path = ft_strndup(tmp->var_value, (size_t)pos - 
// 							(size_t)tmp->var_value - 1);
// 	// if (!new_path)
// 	// 	return (0);
// 	chdir(new_path);
// 	return (new_path);
// }

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
		|| (cmd[1][0] == '~' && !cmd[1][1])))
	{
		if (!cd_home(data))
			return (printf("HOME not set"), 0);
		return (1);
	}
	if (cmd[2])
		return (printf("minishell: cd: too many arguments\n"), 0);
	else if (chdir(cmd[1]) == -1)
	{
		return (perror("chdir: "), 0);
	}
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
