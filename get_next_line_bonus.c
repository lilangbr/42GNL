/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int strinit(char **s, int size, int alloc)
{
	int i;

	if (alloc)
			if (!(*s = malloc(size * sizeof(char)))) 
				return (1); //erro Malloc. Retorna NULL pointer
	i = 0;
	while (i < size)
	{
		(*s)[i] = '\0';
		i++;
	}
	return (0);
}
int get_next_line(int fd, char **line)
{
	ssize_t ret;
	static char *residual[OPEN_MAX]; 
	char **buf;
	int oneline;
	char buffer[BUFFER_SIZE + 1]; //TESTE
	
	if (line == NULL || fd < 0 || fd >= OPEN_MAX || (read(fd, NULL, 0)) || BUFFER_SIZE == 0)
		return (-1);
	/* inicializacoes */
	oneline = 0;
	if (strinit(line, 1, 1) > 0) //Malloc na qtidade necessaria
		return (-1); //erro na MAlloc
	if (!residual[fd]) //NAO EXISTE RESIDUO PARA ESTE FD
		if (strinit(&(residual[fd]), (BUFFER_SIZE + 1), 1) > 0) 
			return (-1); 
	if (!(buf = malloc(sizeof(char *))))
	{
		strfree(line);
		strfree(&residual[fd]);
		return (-1);
	}
	*buf = buffer;
	strinit(buf, BUFFER_SIZE + 1, 0); 
	/* logica */
	while (*(residual[fd])) //!= NULL, i.e, existe resto!
	{
		strcopy(buf, &(residual[fd]), 0);
		zerabuffer(&(residual[fd]), 0, BUFFER_SIZE + 1);
		oneline = splitbuffer(buf, &(residual[fd]));
		if (ft_strappend(line, buf)) //ERRO!
		{
			*buf = NULL; //BUFFER N foi alocado p ser liberado
			free(buf);
			buf = NULL;
			strfree(&(residual[fd]));
			return (-1);
		}
		if (oneline)
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			return (1);
		}
	}
	//NAo tem residuo!
	while ((ret = read(fd, *buf, BUFFER_SIZE) > 0))
	{
		oneline = splitbuffer(buf, &(residual[fd]));
		if (ft_strappend(line, buf))
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			strfree(&(residual[fd]));
			return (-1);
		}
		if (oneline)
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			return (1);
		}
	}
	if (ret == -1)
	{
		*buf = NULL; //strfree(buf);
		free(buf);
		buf = NULL;
		strfree(&(residual[fd]));
		strfree(line);
		return (-1);
	}
	//ret = 0 -> EOF!
	oneline = splitbuffer(buf, &(residual[fd]));
	if (ft_strappend(line, buf))
	{
		*buf = NULL; //strfree(buf);
		free(buf);
		buf = NULL;
		strfree(&(residual[fd]));
		return (-1);
	}
	strfree(&(residual[fd]));
	*buf = NULL;
	free(buf);
	buf = NULL;
	return (0); //EOL ************ e se EOL e Uma linha? O que devolve?
}
