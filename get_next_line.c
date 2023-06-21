/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:47:07 by matsanto          #+#    #+#             */
/*   Updated: 2023/06/14 17:37:01 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static void	*free_variable_memories(char **mem_line, char **mem_rest,
				char **mem_buffer);
static char	*take_single_line(char **rest_content, char **buffer, char **line,
				int buffer_read);
static char	*content_after_line(char *content);
static char	*content_before_line(char *content);

char	*get_next_line(int fd)
/**
  * Lê de um descritor de arquivo e retorna uma linha lida por chamada,
  * incluindo \n, a menos que EOF (encontre o fim do arquivo)
  * e nenhum \n está presente, 
  * nesse caso tudo o que foi lido é retornado imediatamente.
*/
{
	static char	*rest_content;
	char		*line;
	char		*buffer;
	int			buffer_read;

	if (!rest_content)
		rest_content = ft_strdup("");
	line = ft_strdup(rest_content);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	buffer_read = BUFFER_SIZE;
	while (buffer_read == BUFFER_SIZE && (contains_break_position(line) < 0))
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read < 0)
			return (free_variable_memories(&line, &rest_content, &buffer));
		buffer[buffer_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
	return (take_single_line(&rest_content, &buffer, &line, buffer_read));
}

static void	*free_variable_memories(char **mem_line, char **mem_rest,
	char **mem_buffer)
/**
 * Libera as memórias alocadas, limpando as memórias usadas em trabalhos nas outras funções
*/
{
	if (mem_line)
	{
		if (*mem_line)
			free(*mem_line);
		*mem_line = NULL;
	}
	if (mem_rest)
	{
		if (*mem_rest)
			free(*mem_rest);
		*mem_rest = NULL;
	}
	if (mem_buffer)
	{
		if (*mem_buffer)
			free(*mem_buffer);
		*mem_buffer = NULL;
	}
	return (NULL);
}

static char	*take_single_line(char **rest_content, char **buffer,
	char **line, int buffer_read)
/**
 * Ultima parte da função get_next_line. Libera as memórias se necessário,
 * em seguida, vincula a linha de leitura atual que vai ser retornada,
 * e armazena o que sobrou do buffer na variável estática `rest_content`
 * para ter o início da próxima linha salvo para a próxima chamada de função.
*/
{
	if (buffer_read == 0)
	{
		free_variable_memories(NULL, rest_content, buffer);
		if (*line && **line)
			return (*line);
		return (free_variable_memories(line, NULL, NULL));
	}
	free_variable_memories(NULL, rest_content, buffer);
	*rest_content = content_after_line(*line);
	*line = content_before_line(*line);
	return (*line);
}

static char	*content_after_line(char *content)
/**
  * Todo o resto dentro do buffer após o primeiro \n encontrado
  * é salvo na variável estática `rest`. 
  * Isso garante que o início da próxima linha não se perca entre
  * chamadas de função.
*/
{
	int		position;
	int		size;
	char	*content_after;

	position = contains_break_position(content);
	if (position < 0)
		return (NULL);
	size = ft_strlen(content);
	content_after = malloc((size - position) * sizeof(char));
	if (content_after == NULL)
		return (NULL);
	content_after[size - position - 1] = '\0';
	ft_strlcpy(content_after, content + position + 1, size - position);
	return (content_after);
}

static char	*content_before_line(char *content)
/**
 * recorta apenas o início do conteúdo, antes do primeiro \n
*/
{
	int		position;
	char	*content_before;

	position = contains_break_position(content);
	if (!content)
		return (NULL);
	if (position < 0)
		return (content);
	content_before = malloc((position + 2) * sizeof(char));
	if (content_before == NULL)
		return (NULL);
	content_before[position + 1] = '\0';
	ft_strlcpy(content_before, content, position + 2);
	free(content);
	return (content_before);
}