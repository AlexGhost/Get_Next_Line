/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:04:13 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/25 16:45:11 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

int				get_next_line(const int fd, char **line)
{
	static int		bufpos = 0;
	char			*c;
	int				buffer;
	int				i;
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
	buffer = read(fd, c, BUFF_SIZE);
	if (buffer > 0)
	{
		i = 0;
		while (i < BUFF_SIZE && write == 1)
		{
			if (c[i] != '\0')
			{
				if (c[i] == '\n')
				{
					str[i] = '\0';
					bufpos = i;
					write = 0;
				}
				else
					str[i] = c[i];
			}
			i++;
		}
		str[i] = '\0';
		if (write == 1)
			bufpos += BUFF_SIZE;
		printf("bufpos = %i\n", bufpos);
		return (1);
	}
	return (0);
}
