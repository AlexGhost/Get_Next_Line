/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:15:11 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/24 17:28:23 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int			readlinewidth(int fd)
{
	char	buff[2];
	size_t	nbread;

	(void)memset((void*)buff, 0, (size_t) 2);
	nbread = read(fd, (void*) buff, (size_t)2);
	if (nbread == -1 || nbread == 0)
		return (-1);
	buff[1] = '\0';
	return (atoi(buff));
}

void		readandprintlines(int fd, size_t linewidth)
{
	char	*buff;
	size_t	nbread;

	buff = (char*)malloc((linewidth + 1) * sizeof(*buff));
	if (buff == NULL)
		return ;
	(void) memset((void*) buff, 0, linewidth + 1);
	while ((nbread = read(fd, (void*) buff, linewidth)) != 0)
	{
		printf("%s", buff);
		(void) memset((void*) buff, 0, linewidth);
	}
	free(buff);
	return ;
}

int			main(int ac, char **av)
{
	int fd;
	int linewidth;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (-1);
		linewidth = readlinewidth(fd);
		if (linewidth == -1 || linewidth == 0)
			return (-1);
		readandprintlines(fd, (size_t) linewidth);
		close(fd);
	}
	return (0);
}
