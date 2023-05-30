/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/30 14:47:26 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	ft_pwd(t_data *data)
{
	char	*line;

	(void)data;
	line = getcwd(NULL, 0);
	if (!line)
		return (perror("pwd: "), 0);
	printf("%s\n", line);
	free(line);
	return (1);
}

static int	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
	return (1);
}

static void	ft_exit(t_data *data, char **str)
{
	printf("exit\n");
	if (str[1])
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
	free_all(data);
	if (data->stdin_save > 0 && data->stdout_save > 0)
	{
		if (close(data->stdin_save) == -1 || close(data->stdout_save) == -1)
			return (perror("Error with closing STDIN/STDOUT saves"));
	}
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
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)
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
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)
		return (SUCCESS);
	else if ((ft_strncmp(cmd[0], "exit", 4) == 0) && len == 4)
		return (SUCCESS);
	return (NOT_BUILTIN);
}
