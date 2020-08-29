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

static int strinit(char **s, int size) //REDUNDANTE?
{
	if (!(*s = malloc(size * sizeof(char)))) 
		return (1); //erro Malloc. Retorna NULL pointer
	(*s)[size - 1] = '\0';
	zerabuffer(s, 0);
	return (0);
}
int get_next_line(int fd, char **line)
{
	ssize_t ret;
	static char *residual; //AINDA N VOU MEXER C OPEN_MAX
	char **buf;
	int oneline;
	char buffer[BUFFER_SIZE + 1]; //TESTE
	
	/* inicializacoes */
	buffer[BUFFER_SIZE] = '\0';
	oneline = 0;
	if (strinit(line, 1) < 0) //Malloc na qtidade necessaria
		return (-1); //erro na MAlloc
	if (!residual) //NAO EXISTE RESIDUO PARA ESTE FD
		if (strinit(&(residual), (BUFFER_SIZE + 1)) < 0) //Malloc na qtidade necessaria
			return (-1); //erro na MAlloc
	if (!(buf = malloc(sizeof(char *))))
	{
		strfree(line);
		strfree(&residual);
		return (-1);
	}
	*buf = buffer;
	zerabuffer(buf, 0);
	/* logica */
	if (residual)
	{ //ja estava sendo trabalhado o residual[fd]
		while (*(residual)) //!= NULL, i.e, existe resto!
		{
			strcopy(buf, &(residual), 0);
			zerabuffer(&(residual), 0);
			oneline = splitbuffer(buf, &(residual));
			if (ft_strappend(line, buf)) //ERRO!
			{
				*buf = NULL; //strfree(buf); -> Nao posso fazer pois BUFFER N foi alocado p ser liberado
				free(buf);
				buf = NULL;
				strfree(&(residual));
				//strfree(line);
				return (-1);
			}
			if (oneline)
			{
				*buf = NULL; //strfree(buf);
				free(buf);
				buf = NULL;
				//strfree(line);
				return (1);
			}
		}
	}
	//NAo tem residuo!
	while ((ret = read(fd, *buf, BUFFER_SIZE) > 0))
	{
		oneline = splitbuffer(buf, &(residual));
		if (ft_strappend(line, buf))
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			strfree(&(residual));
			//strfree(line);
			return (-1);
		}
		if (oneline)
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			//strfree(line);
			return (1);
		}
	}
	//ret = 0 -> EOF!
	oneline = splitbuffer(buf, &(residual));
	//if (*buf) //EXISTE LINHA!!!
	//	oneline = 1;
	if (ft_strappend(line, buf))
	{
		*buf = NULL; //strfree(buf);
		free(buf);
		buf = NULL;
		strfree(&(residual));
		//strfree(line);
		return (-1);
	}
	//if (oneline)
	//	return (1);
	strfree(&(residual));
	//free(*buf); //************************************
	*buf = NULL;
	free(buf);
	buf = NULL;
	//strfree(line);
	return (0); //EOL ************************************ e se EOL e Uma linha? O que devolve?
}
