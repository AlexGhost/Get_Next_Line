/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:04:13 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/25 19:36:20 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int				get_next_line(const int fd, char **line)
{
	static int		bufpos = 0;
	static char		reste[BUFF_SIZE + 1] = "\0";
	char			*c;
	int				buffer;
	int				i;
	int				j;
	int				k;
	char			*str;
	int				write;

	if (fd <= 0)
		return (-1);
	buffer = 0;
	write = 1;
	if (!line)
		return (-1);
	str = *line;
	c = ft_strnew(BUFF_SIZE + 1);
	// GESTION RESTE
	if (reste[0] != '\0')
	{
		i = 0;
		j = 0;
		while (reste[i] == '\n')
		{
			i++;
		}
		while (reste[i] != '\n' && reste[i] != '\0')
		{
			str[j] = reste[i];
			j++;
			i++;
		}
		j = 0;
		while (j < i)
		{
			reste[j] = reste[i];
			j++;
		}
	}
	// GESTION NON RESTE
	if (reste[0] == '\0')
	{
		if ((buffer = read(fd, c, BUFF_SIZE)) > 0)
		{
			i = 0;
			printf("buffer = %i\n", buffer);
			while (c[i] != '\0' && c[i] != '\n')
			{
				str[i] = c[i];
				i++;
			}
			str[i] = '\0';
			j = 0;
			while (c[i] != '\0')
			{
				reste[j] = c[i];
				j++;
				i++;
			}
			reste[j] = '\0';
			printf("reste = %s\n", reste);
			return (1);
		}
	}
	if (buffer == -1)
	{
		printf("errno = %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}
