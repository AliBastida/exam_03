/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastida <abastida@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:20:49 by abastida          #+#    #+#             */
/*   Updated: 2023/12/07 17:25:12 by abastida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	(void)ac;
	int fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);

	while (line)
	{
		printf("--%s--\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
