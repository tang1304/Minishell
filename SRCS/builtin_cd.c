/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 08:38:05 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
		return (1);
	}
	return (perror("getcwd: "), 0);
}
