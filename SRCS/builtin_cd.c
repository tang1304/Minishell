/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/25 14:22:03 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	var_array_replacement(t_data *data, char *var, char *new)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		if (ft_strncmp(data->envp[i], var, ft_strlen(var) - 1) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin(var, new);
			return (1);
		}
	}
	return (0);
}

static int	pwds_handling(t_data *data)
{
	char	*current;
	int		check_1;
	int		check_2;
	int		check_3;
	int		check_4;

	current = getcwd(NULL, 0);
	if (current != NULL)
	{
		check_1 = replace_env(data, "OLDPWD", search_env(data, "PWD"));
		if (check_1 == -1)
			return (-1);
		check_2 = replace_env(data, "PWD", current);
		if (check_2 == -1)
			return (-1);
		check_3 = var_array_replacement(data, "OLDPWD=", search_env(data, "OLDPWD"));
		if (check_3 == -1)
			return (-1);
		check_4 = var_array_replacement(data, "PWD=", current);
		if (check_4 == -1)
			return (-1);
		free(current);
		return (1);
	}
	return (0);
}

static int	cd_home(t_data *data)
{
	char	*home;
	int		check;

	home = search_env(data, "HOME");
	if (home == NULL)
		return (0);
	chdir(home);
	check = pwds_handling(data);
	if (check == -1)
		return (0);
	if (check == 0)
		return (perror("getcwd: "), -1);
	return (1);
}

int	ft_cd(t_data *data, char **cmd)
{
	int		home_check;
	int		check;

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
	check = pwds_handling(data);
	if (check == -1)
		return (0);
	if (check == 0)
		return (perror("getcwd: "), -1);
	return (1);
}
