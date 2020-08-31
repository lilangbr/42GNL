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

#include "get_next_line.h"

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
	static char *residual; 
	char **buf;
	int oneline;
	char buffer[BUFFER_SIZE + 1]; 
	
	
	if (line == NULL || fd < 0 || fd > OPEN_MAX || BUFFER_SIZE == 0)
		return (-1);
	/* inicializacoes */
	oneline = 0;
	if (strinit(line, 1, 1) < 0) //Malloc na qtidade necessaria
		return (-1); //erro na MAlloc
	if (!residual) //NAO EXISTE RESIDUO PARA ESTE FD
		if (strinit(&(residual), (BUFFER_SIZE + 1), 1) < 0) //Malloc na qtidade necessaria
			return (-1); //erro na MAlloc
	if (!(buf = malloc(sizeof(char *))))
	{
		strfree(line);
		strfree(&residual);
		return (-1);
	}
	*buf = buffer;
	strinit(buf, BUFFER_SIZE + 1, 0); 
	/* logica */
	while (*(residual)) //!= NULL, i.e, existe resto!
	{
		strcopy(buf, &(residual), 0);
		zerabuffer(&(residual), 0);
		oneline = splitbuffer(buf, &(residual));
		if (ft_strappend(line, buf)) //ERRO!
		{
			*buf = NULL; //BUFFER N foi alocado p ser liberado
			free(buf);
			buf = NULL;
			strfree(&(residual));
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
		oneline = splitbuffer(buf, &(residual));
		if (ft_strappend(line, buf))
		{
			*buf = NULL;
			free(buf);
			buf = NULL;
			strfree(&(residual));
			return (-1);
		}
		if (oneline)
		{
			*buf = NULL;
			free(buf);
			buf = NULL;
			return (1);
		}
	}
	if (ret == -1)
	{
		strfree(line);
		return (-1);
	}
	//ret = 0 -> EOF!
	oneline = splitbuffer(buf, &(residual));
	if (ft_strappend(line, buf))
	{
		*buf = NULL; 
		free(buf);
		buf = NULL;
		strfree(&(residual));
		return (-1);
	}
	strfree(&(residual));
	*buf = NULL;
	free(buf);
	buf = NULL;
	return (0); //EOL ******** e se EOL e Uma linha? O que devolve?
}
