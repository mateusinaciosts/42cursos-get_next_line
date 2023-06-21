/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:47:14 by matsanto          #+#    #+#             */
/*   Updated: 2023/06/17 18:26:02 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("exemplo.txt", O_RDONLY);
	gnl = get_next_line(fd);
	printf("%s", gnl);
	printf("2 tentativa:\n");
	gnl = get_next_line(fd);
	printf("%s", gnl);
	close(fd);
	return (0);
}
/*
** clear && cc -Wall -Wextra -Werror *.c -D BUFFER_SIZE=1 && ./a.out | cat -e
** clear && cc -Wall -Wextra -Werror *.c -D BUFFER_SIZE=42 && ./a.out | cat -e
** clear && cc -Wall -Wextra -Werror *.c -D BUFFER_SIZE=10000 && ./a.out | cat -e
*/