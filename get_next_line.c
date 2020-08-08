/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int ft_strlen(const char *s)
{
	if (!s)
		return (0);
	if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}
static int endofline(char *s)
{
	int pos;

	pos = -1;
	if (!(*s))
		return (pos);
	pos = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == '\n')
			return (pos);
		pos++;
	}
	if (pos == ft_strlen(s))
		return (-2);
	else
		return (-1);
}
static void ft_strappend(char **dst, char **add)
{
	size_t size;
	size_t i;
	size_t j;
	char *aux;
	char resto[10];

	*dst = malloc(1*sizeof(char)); //gnl
	**dst = '\0'; 				//gnl
	if (endofline(*add) < 0)
		size = ft_strlen(*dst) + ft_strlen(*add) + 1;
	else
		size = ft_strlen(*dst) + endofline(*add) + 1;
	aux = malloc(size * sizeof(char));
    i = 0;
	j = 0;
	while (*dst[i])
	{
		aux[i] = *dst[i];
		i++;
	}
	while (**add != '\0' && **add != '\n')
	{
		aux[i] = **add;
		i++;
		j++;
		(*add)++;
	}
	aux[i] = '\0';
	free(*dst);
	*dst = malloc(size*sizeof(char));
	**dst = *aux;
	(*dst)++;
	aux++;
	**dst = *aux;
	(*dst)++;
	aux++;
	**dst = *aux;
	aux--;
	aux--;
	free(aux);
	(*dst)--;
	(*dst)--;
	resto[0] = (*add)[1];
	resto[1] = (*add)[2];
	resto[2] = (*add)[3];
	resto[3] = (*add)[4];
	resto[4] = (*add)[5];
	resto[5] = (*add)[6];
	resto[6] = '\0';
	printf("%s\n", resto);
}
int main()
{
	char **s_main;
	char **buf;
    char buffer[10] = "oi\nmenina";
	char **final;

	s_main = malloc(1*sizeof(char*));
	buf = malloc(1*sizeof(char*));
	*buf = buffer;
	ft_strappend(s_main, buf);
	final = s_main;
	printf("%s\n", *final);
	return 0;
}
