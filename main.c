/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:15:11 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/23 18:25:34 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>

char		**newline(int size)
{
	char	**line;
	int		i;

	line = (char**)malloc(sizeof(char*) * size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		line[i] = (char*)malloc(sizeof(char) * size + 1);
		line[i] = "\0";
		i++;
	}
	line[i] = NULL;
	return (line);
}

int			main(int ac, char **av)
{
	int gnl;
	int fd;
	char **line;

	if (ac == 2)
	{
		line = newline(5);
		fd = open(av[1], O_RDONLY);
		while ((gnl = get_next_line(fd, line)))
		{
		}
		close(fd);
	}
	return (0);
}
