/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:47:07 by matsanto          #+#    #+#             */
/*   Updated: 2023/06/11 18:45:37 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*free_n_null(char **s1, char **s2, char **s3);
static char	*copy_up_to_nl(char *string);
static char	*save_past_first_nl(char *source);
static char	*return_line(char **rest, char **buffer, char **line, int i);

char	*get_next_line(int fd)
/**
 * Esta função lê a partir de um descritor de ficheiro e devolve uma linha lida
 * por chamada, definida doravante como uma string que termina em \n, a menos que EOF
 * seja alcançado e nenhum \n esteja presente, caso em que tudo o que foi lido
 * é devolvido de uma só vez.
*/
{
	static char	*rest;
	char		*buffer;
	char		*line;
	int			chars_read;

	// inicializar variáveis
	if (!rest)
		rest = ft_strdup("");
	line = ft_strdup(rest);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	chars_read = BUFFER_SIZE;

	// loop usando read() enquanto não for encontrado \n
	while (chars_read == BUFFER_SIZE && !(contains_nl(line) >= 0))
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		
		// terminar a execução se a leitura do ficheiro correr mal
		if (chars_read < 0) 
			return (free_n_null(&line, &rest, &buffer));
		buffer[chars_read] = '\0';

		// concatena a memória intermédia lida com a linha que está a ser construída
		line = ft_strjoin(line, buffer);
	}
	return (return_line(&rest, &buffer, &line, chars_read));
}

static void	*free_n_null(char **s1, char **s2, char **s3)
/**
 * Liberta a memória atribuída e define os apontadores como NULL
*/
{
	if (s1)
	{
		if (*s1)
			free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		if (*s2)
			free(*s2);
		*s2 = NULL;
	}
	if (s3)
	{
		if (*s3)
			free(*s3);
		*s3 = NULL;
	}
	return (NULL);
}

static char	*copy_up_to_nl(char *string)
/**
 * amarra a linha até o primeiro \n encontrado na string.
*/
{
	char	*copy;
	int		nl_pos;

	nl_pos = contains_nl(string);
	if (!string)
		return (NULL);
	if (!(nl_pos >= 0))
		return (string);
	copy = malloc((nl_pos + 2) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	copy[nl_pos + 1] = '\0';
	ft_strlcpy(copy, string, nl_pos + 2);
	free(string);
	return (copy);
}

static char	*save_past_first_nl(char *source)
/**
 * Todo o resto dentro do buffer após o primeiro \n encontrado
 * é guardado na variável estática `rest`. Isto garante
 * que o início da próxima linha não seja perdido entre
 * chamadas de função.
*/
{
	char	*dest;
	int		nl_pos;
	int		strlen;

	nl_pos = contains_nl(source);
	if (!(nl_pos >= 0))
		return (NULL);
	dest = malloc(((strlen = ft_strlen(source)) - nl_pos) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[strlen - nl_pos - 1] = '\0';
	ft_strlcpy(dest, source + nl_pos + 1, strlen - nl_pos);
	return (dest);
}

static char	*return_line(char **rest, char **buffer, char **line, int i)
/**
 * Finaliza a execução de get_next_line. Libera memória se necessário,
 * então amarra a linha de leitura atual para ser retornada,
 * e armazena o que sobrou do buffer na variável estática `rest`
 * para que o início da próxima linha seja guardado para a próxima chamada da função.
*/
{
	if (i == 0)
	{
		free_n_null(rest, buffer, NULL);
		if (*line && **line)
			return (*line);
		return (free_n_null(line, NULL, NULL));
	}
	free_n_null(rest, buffer, NULL);
	*rest = save_past_first_nl(*line);
	*line = copy_up_to_nl(*line);
	return (*line);
}
