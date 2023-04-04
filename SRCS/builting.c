/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/03 14:26:51 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	builtins(t_data data, char **cmd)
{
	int	len;

	len = ft_strlen(cmd[0]) - 1;
	if ((ft_strncmp(cmd[0], "echo", 4) == 0) && len == 4)
		ft_echo(cmd);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0) && len == 2)
		ft_cd(cmd);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0) && len == 3)
		ft_pwd();
	else if ((ft_strncmp(cmd[0], "export", 6) == 0) && len == 6)
		ft_export();
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0) && len == 5)
		ft_unset();
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)
		ft_env();
	else if ((ft_strncmp(cmd[0], "exit", 5) == 0) && len == 5)
		ft_exit();
}

void	ft_echo(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && !cmd[1][2])
	{
		i++;
		while (cmd[++i])
			printf("%s", cmd[i]);
	}
	else
	{
		while (cmd[++i])
			printf("%s", cmd[i]);
		write(1, "\n", 1);
	}
}

void	ft_cd(char **cmd)
{
	int	i;

	i = 0;
	;
}

void	ft_export(t_data *data, char **cmd)
{
	int	i;

	if (!cmd[1] || cmd[1][0] == '\0')
		ft_env(data);
	i = 0;
	while (cmd[++i])
	{
		;
	}
}

void	ft_pwd(t_data *data, char **cmd)
{
	char	*line;

	line = getcwd(NULL, 0);
	printf("%s\n", line);
	free(line);
}

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
	{
		printf("%s\n", data->envp[i]);
	}
}

void	ft_exit(char **str)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
