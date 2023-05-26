/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/18 12:41:12 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_pwd(t_data *data)
{
	char	*line;

	line = search_env(data, "PWD");
	printf("%s\n", line);
	return (1);
}

static int	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->var_value && ft_strchr(tmp->var_name, '='))
		{
			printf("%s", tmp->var_name);
			printf("%s\n", tmp->var_value);
		}
		tmp = tmp->next;
	}
	return (1);
}

static void	ft_exit(t_data *data, char **str)
{
	printf("exit\n");
	if (str[1])
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
	free_all(data);
	exit(EXIT_SUCCESS);
}

int	builtins(t_data *data, char **cmd)
{
	int	len;
	int	check;

	check = 0;
	len = ft_strlen(cmd[0]);
	if ((ft_strncmp(cmd[0], "echo", 4) == 0) && len == 4)
		check = ft_echo(cmd);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0) && len == 2)
		check = ft_cd(data, cmd);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0) && len == 3)
		check = ft_pwd(data);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0) && len == 6)
		check = ft_export(data, cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0) && len == 5)
		check = ft_unset(data, cmd);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)// a tester apres un export/unset
		check = ft_env(data);
	else if ((ft_strncmp(cmd[0], "exit", 4) == 0) && len == 4)
		ft_exit(data, cmd);
	return (check);
}

int	check_builtins(char **cmd)
{
	int	len;

	len = ft_strlen(cmd[0]);
	if ((ft_strncmp(cmd[0], "echo", 4) == 0) && len == 4)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0) && len == 2)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0) && len == 3)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0) && len == 6)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0) && len == 5)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)// a tester apres un export/unset
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "exit", 4) == 0) && len == 4)
		return (SUCCESS);
	return (NOT_BUILTIN);
}