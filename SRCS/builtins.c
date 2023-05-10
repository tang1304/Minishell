/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 08:19:49 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	ft_pwd(t_data *data)
{
	char	*line;

	line = search_env(data, "PWD");
	printf("%s\n", line);
	free(line);
}

static void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->envp[++i])
		printf("%s\n", data->envp[i]);
}

static void	ft_exit(char **str)
{
	printf("exit\n");
	if (str[1])
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
	exit(EXIT_SUCCESS);
}

void	builtins(t_data *data, char **cmd)
{
	int	len;

	len = ft_strlen(cmd[0]);
	if ((ft_strncmp(cmd[0], "echo", 4) == 0) && len == 4)
		ft_echo(cmd);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0) && len == 2)
		ft_cd(data, cmd);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0) && len == 3)
		ft_pwd(data);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0) && len == 6)
		ft_export(data, cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0) && len == 5)
		ft_unset(data, cmd);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)// a tester apres un export/unset
		ft_env(data);
	else if ((ft_strncmp(cmd[0], "exit", 4) == 0) && len == 4)
		ft_exit(cmd);
}
