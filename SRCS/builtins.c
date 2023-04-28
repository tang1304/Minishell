/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:36:28 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/28 11:09:58 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	builtins(t_data *data, char **cmd)
{
	int	len;

	len = ft_strlen(cmd[0]) - 1;
	if ((ft_strncmp(cmd[0], "echo", 4) == 0) && len == 4)
		ft_echo(cmd);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0) && len == 2)
		ft_cd(data, cmd);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0) && len == 3)
		ft_pwd(data);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0) && len == 6)
		ft_export(data, cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0) && len == 5)
		ft_unset();
	else if ((ft_strncmp(cmd[0], "env", 3) == 0) && len == 3)
		ft_env(data);
	else if ((ft_strncmp(cmd[0], "exit", 5) == 0) && len == 5)
		ft_exit(cmd);
}

int	ft_cd(t_data *data, char **cmd)
{
	char	*home;
	t_env	*tmp;
	int		i;

	if (cmd[2])
		return (printf("minishell: cd: too many arguments"), 0);
	tmp = data->env;
	if (cmd[0] && (!cmd[1] || cmd[1][0] == '\0' || cmd[1][0] == '~'))
	{
		while (tmp->next != NULL)
		{
			if (ft_strncmp(tmp->var_name, "HOME", 4))
			{
				home = ft_strdup(tmp->var_value);
				// if (!home)
				// 	;
				chdir(home);
				free (home);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	if (chdir(cmd[1]) == -1)
		return (perror("chdir: "), 0);
	else
	{
		i = 0;
		while (i <)
	}
}

void	ft_pwd(t_data *data)
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
	if (str[1])
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
	exit(EXIT_SUCCESS);
}
