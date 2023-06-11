/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:47:19 by matsanto          #+#    #+#             */
/*   Updated: 2023/06/11 18:59:17 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

size_t	ft_strlen(const char *s)
/**
  * Retorna o comprimento de uma string válida
*/
{
	int	qtd_caracteres;

	qtd_caracteres = 0;
	while (*s)
	{
		qtd_caracteres++;
		s++;
	}
	return (qtd_caracteres);
}

char	*ft_strdup(const char *s)
/**
  * duplica uma string em outra. aloca memória usando malloc.
*/
{
	unsigned int	strlength;
	char			*newstr;
	unsigned int	i;

	strlength = ft_strlen(s);
	newstr = malloc((strlength + 1) * sizeof(const char));
	if (newstr == NULL)
		return (NULL);
	newstr[strlength] = '\0';
	i = 0;
	while (i < strlength)
	{
		((char *) newstr)[i] = ((char *) s)[i];
		i++;
	}
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
/**
  * concatena duas strings de comprimento fixo em uma.
  * aloca memória usando malloc.
*/
{
	char	*joint;
	int		i;
	int		length_s1;
	int		length_s2;

	length_s1 = ft_strlen(s1);
	length_s2 = ft_strlen(s2);
	joint = malloc((length_s1 + length_s2 + 1) * sizeof(char));
	if (joint == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		joint[i] = s1[i];
	i = -1;
	while (s2[++i])
		joint[i + length_s1] = s2[i];
	joint[length_s1 + length_s2] = '\0';
	free((char *)s1);
	return (joint);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
/**
  * copia (até tamanho bytes) o conteúdo de uma string (src) em outra (dst).
  * substitui o conteúdo de dst.
*/
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int	contains_nl(char *string)
/**
  * verifica uma string em busca de um caractere de linha única (\n).
  * se encontrado, retorna sua posição (>= 0).
  * caso contrário, retorna -1.
*/
{
	int	i;

	if (!string)
		return (-1);
	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
