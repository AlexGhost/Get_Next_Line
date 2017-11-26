/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:04:13 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/26 16:49:01 by acourtin         ###   ########.fr       */
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
	tmp = ft_strnew((size_t) ft_strlen(*remain));
	ft_strcpy(tmp, *remain);
	*remain = NULL;
	*remain = ft_strnew((size_t) (ft_strlen(tmp) + BUFF_SIZE));
	ft_strcpy(*remain, tmp);
	return (1);
}

static int		to_line(int buffer, char **remain, char **line)
{
	int i;
	int j;

	i = 0;
	if (buffer != 0 || ft_strlen(*remain) != 0)
	{
		while ((*remain)[i] != '\n')
		{
			(*line)[i] = (*remain)[i];
			i++;
			if (!(*remain)[i])
				break ;
		}
		(*line)[i] = '\0';
		i++;
		if ((*remain)[0] != '\n')
		{
			j = 0;
			while ((*remain)[i])
			{
				(*remain)[j] = (*remain)[i];
				i++;
				j++;
			}
			(*remain)[j] = '\0';
			return (1);
		}
		j = 0;
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
	static int	r = 0;
	static char	*remain;
	int			buffer;

	if ((!remain && !(remain = ft_strnew(1))) || !(*line = ft_strnew(BUFF_SIZE)) || fd < 0)
		return (-1);
	if (r == 1)
		return (0);
	while ((buffer = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if (remalloc(&remain) == 0)
			return (-1);
		remain = ft_strcat(remain, *line);
		if (ft_strchr(*line, '\n'))
			break ;
	}
	if (to_line(buffer, &remain, line) == 1)
	{
		//printf("line = %s\nremain = %s\n", *line, remain);
		if (ft_memcmp((*line) + 1, remain, ft_strlen(remain)) == 0)
			r = 1;
		return (1);
	}
	else if (ft_memcmp(*line, remain, ft_strlen(*line)) == 0)
	{
		if (ft_strcmp(ft_strdup(""), *line) != 0)
			return (1);
		return (0);
	}
	return (1);
}
