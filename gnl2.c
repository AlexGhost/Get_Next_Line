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

static int		remalloc(char **save)
{
	char *tmp;

	if (!(*save))
		return (0);
	tmp = ft_strnew(ft_strlen(*save));
	ft_strcpy(tmp, *save);
	*save = NULL;
	*save = ft_strnew(ft_strlen(tmp) + BUFF_SIZE);
	ft_strcpy(*save, tmp);
	return (1);
}

int				process(char *buf, char **save, char **line)
{
	int i;

	i = 0;
	if (ft_strchr(buf, '\n'))
	{
		while(buf[i] != '\n')
		{
			(*line)[i] = buf[i];
			i++;
		}
		(*line)[i] = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*save;
	int			b;
	char		*buf;

	if ((!save && !(save = ft_strnew(BUFF_SIZE))) \
		|| !(*line = ft_strnew(BUFF_SIZE)) \
		|| !(buf = ft_strnew(BUFF_SIZE)) \
		|| fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	while ((b = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (remalloc(&save) == 0)
			return (-1);
		//ft_strncat(save, buf, BUFF_SIZE);
		if (ft_memchr(buf, '\n', BUFF_SIZE))
			break ;
	}
	if (process(buf, &save, line) == 1)
		return (1);
	return (0);
}
