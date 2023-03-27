/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:42:03 by rrebois           #+#    #+#             */
/*   Updated: 2023/01/02 10:42:11 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static char	*ft_extract_line(char *temp)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	if (temp == NULL || temp[i] == '\0')
		return (NULL);
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	ptr = (char *)malloc(sizeof(*ptr) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ptr[j] = temp[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static char	*ft_new_str(char *temp)
{
	size_t	i;
	size_t	j;
	char	*new_temp;

	i = 0;
	j = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	if (temp[i] == '\0')
		return (free(temp), NULL);
	new_temp = (char *)malloc(sizeof(*new_temp) * (ft_strlen(temp) - i + 1));
	if (new_temp == NULL)
		return (NULL);
	while (temp[i] != '\0')
		new_temp[j++] = temp[i++];
	new_temp[j] = '\0';
	return (free(temp), new_temp);
}

static int	ft_check(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read_file(int fd, char *temp)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	if (temp == NULL)
	{
		temp = (char *)malloc(sizeof(*temp) * 1);
		if (temp == NULL)
			return (NULL);
		temp[0] = '\0';
	}
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (free(temp), NULL);
		buf[ret] = '\0';
		temp = ft_strjoin_gnl(temp, buf);
		if (temp == NULL)
			return (NULL);
		if (ft_check(temp) == 1)
			break ;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*ptr;

	ptr = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (temp)
			temp[0] = '\0';
		return (NULL);
	}
	temp = ft_read_file(fd, temp);
	if (temp == NULL)
		return (NULL);
	ptr = ft_extract_line(temp);
	temp = ft_new_str(temp);
	return (ptr);
}
