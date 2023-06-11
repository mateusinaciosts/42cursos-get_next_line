/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:47:14 by matsanto          #+#    #+#             */
/*   Updated: 2023/06/11 19:48:01 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// FILE, fopen()
#include <stdio.h> // printf()
#include <stdlib.h> // free()

char	*g_file_name = "./exemplo";
FILE	*g_fp;

char	*get_next_line(int fd);

int main()
/**
* - A função main() abre um ficheiro num descritor de ficheiro (fd / _fileno).
* - Este ficheiro contém texto destinado a ser lido uma linha de cada vez através
* da função get_next_line().
* Cada chamada deve retornar uma string de caracteres terminada com um '\n', desde que
* que exista um. Linhas vazias são retornadas da mesma forma (um único '\n' por chamada).
* main() continua a imprimir a linha resultante lida por get_next_line(),
* fazendo um loop pelo arquivo.
* Quando EOF é atingido, get_next_line() retorna NULL e pára a execução;
* main() fecha o ficheiro, e o programa pára.
**/

{
	char	*linha;
	int		i = 0;

	g_fp = fopen(g_file_name, "r");
	
	while((linha = get_next_line(g_fp->_fileno)) != NULL)
	{
		printf("Line %i >>> %s", i++, linha);
		free(linha);
	}
	
	fclose(g_fp);
	return (0);
}