/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:04:13 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/26 17:40:19 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static int		remalloc(char **remain)
{
	char *tmp;

	if (!(*remain))
		return (0);
	tmp = ft_strnew(ft_strlen(*remain));
	ft_strcpy(tmp, *remain);
	*remain = NULL;
	*remain = ft_strnew(ft_strlen(tmp) + BUFF_SIZE);
	ft_strcpy(*remain, tmp);
	return (1);
}

static int		to_line(int buffer, char **remain, char **line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (buffer != 0 || ft_strlen((*remain)) != 0)
	{
		while ((*remain)[i] != '\n')
		{
			(*line)[i] = (*remain)[i];
			i++;
		}
		(*line)[i] = '\0';
		i++;
		if ((*remain)[0] == '\n')
		{
			while ((*remain)[i])
			{
				(*remain)[j] = (*remain)[i];
				i++;
				j++;
			}
			(*remain)[j] = '\0';
			return (1);
		}
		while ((*remain)[i])
		{
			(*remain)[j] = (*remain)[i];
			i++;
			j++;
		}
		(*remain)[j] = '\0';
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*remain;
	int			buffer;

	if ((!remain && !(remain = ft_strnew(BUFF_SIZE))) || !(*line = ft_strnew(BUFF_SIZE)) || fd < 0)
		return (-1);
	while ((buffer = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if (remalloc(&remain) == 0)
			return (-1);
		ft_strncat(remain, *line, BUFF_SIZE);
		if (ft_memchr(*line, '\n', BUFF_SIZE))
			break ;
	}
	//printf("line = %s\nremain = %s\n", *line, remain);
	if (to_line(buffer, &remain, line) == 1)
	{
		return (1);
	}
	//printf("line = %s\nremain = %s\n", *line, remain);
	if (ft_memcmp(*line, remain, ft_strlen(*line)) == 0)
	{
		if (!(*line = ft_strdup("")))
			return (1);
		return (0);
	}
	return (1);
}
