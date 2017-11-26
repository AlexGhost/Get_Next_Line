/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maino.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 17:37:31 by acourtin          #+#    #+#             */
/*   Updated: 2017/11/26 15:26:31 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int			main(int ac, char **av)
{
	int fd;
	char *line;
	int gnl;
	int i;

	if (ac == 2)
	{
		i = 0;
		line = ft_strnew(BUFF_SIZE + 1);
		fd = open(av[1], O_RDONLY);
		while ((gnl = get_next_line(fd, &line)) == 1)
		{
			printf("finalline = %s", line);
			printf("\n");
			free(line);
			line = ft_strnew(BUFF_SIZE + 1);
			i++;
		}
		if (gnl == -1)
			printf("GNL failed\n");
		else if (gnl == 0)
			printf("GNL success\n");
		else
			printf("what ?!\n");
		free(line);
	}
	return (0);
}
