/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:04:13 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/25 18:48:05 by acourtin         ###   ########.fr       */
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
	i = 0;
	if (!line)
		return (-1);
	str = *line;
	c = ft_strnew(BUFF_SIZE + 1);
	buffer = read(fd, c, BUFF_SIZE);
	printf("buffer = %i\n", buffer);
	if (buffer == -1)
	{
		printf("errno = %s\n", strerror(errno));
		return (-1);
	}
	j = 0;
	while (reste[j])
	{
		str[j] = reste[j];
		j++;
	}
	i = 0;
	while (c[i] == '\n')
		i++;
	if (buffer > 0)
	{
		while (write == 1 && c[i] != '\0')
		{
			if (i >= BUFF_SIZE - 1)
			{
				buffer = read(fd, c, BUFF_SIZE);
				i = 0;
			}
			if (c[i] == '\n' || c[i] == '\0')
			{
				str[j] = '\0';
				bufpos += i;
				write = 0;
			}
			else
			{
				str[j] = c[i];
				i++;
				j++;
			}
		}
		while (c[i] == '\n')
			i++;
		k = 0;
		while (c[i] != '\0' && c[i] != '\n')
		{
			reste[k] = c[i];
			i++;
			k++;
		}
		//printf("reste = %s\n", reste);
		i = 0;
		str[j] = '\0';
		if (write == 1)
			bufpos += BUFF_SIZE;
		printf("bufpos = %i\n", bufpos);
		return (1);
	}
	return (0);
}
