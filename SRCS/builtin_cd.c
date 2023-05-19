/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/19 13:47:33 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	cd_home(t_data *data)
{
	char	*home;
	char	*current;
	int		check_1;
	int		check_2;

	home = search_env(data, "HOME");
	if (home == NULL)
		return (0);
	chdir(home);
	current = getcwd(NULL, 0);
	if (current != NULL)
	{
		check_1 = replace_env(data, "OLDPWD", search_env(data, "PWD"));
		check_2 = replace_env(data, "PWD", current);
		if (check_1 == -1 || check_2 == -1)
			return (-1);
		return (1);
	}
	return (perror("getcwd: "), -1);
}

int	ft_cd(t_data *data, char **cmd)//Ne remplace PAS dans data->env, a fix
{
	char	*current;
	int		home_check;
	int		check_1;
	int		check_2;

	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0' \
		|| (cmd[1][0] == '~' && !cmd[1][1])))
	{
		home_check = cd_home(data);
		if (home_check == 0)
			return (printf("minishell: cd: HOME not set\n"), 1);
		if (home_check == -1)
			return (-1);
		return (1);
	}
	if (cmd[2])
		return (printf("minishell: cd: too many arguments\n"), 1);
	else if (chdir(cmd[1]) == -1)
		return (perror("chdir: "), -1);
	current = getcwd(NULL, 0);
	printf("current: %s\n", current);
	if (current != NULL)
	{
		check_1 = replace_env(data, "OLDPWD", search_env(data, "PWD"));
		check_2 = replace_env(data, "PWD", current);
		if (check_1 == -1 || check_2 == -1)
			return (-1);
		return (1);
	}
	return (perror("getcwd: "), -1);
}
