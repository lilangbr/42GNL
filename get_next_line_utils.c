/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(const char *s)
{
	if (!s)
		return (-1);
	else if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}
void strfree(char **s) 
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}
void strcopy(char **dst, char **src, int start)
{ 
	int i;
	int j;

	i = 0;
	j = start;
	while ((*src)[j]) 
	{
		(*dst)[i] = (*src)[j];
		(*src)[j] = '\0';
		i++;
		j++;
	}
	(*dst)[i] = '\0';
}
int ft_strappend(char **dst_line, char **add_buff)
{  //add nao tem /n!!
	size_t size;
	size_t i;
	size_t j;
	char *aux;
	
	size = ft_strlen(*dst_line) + ft_strlen(*add_buff) + 1; 
	if (!(aux = malloc(size * sizeof(char)))) 
		return (1);
    i = 0;
	j = 0;
	while ((*dst_line)[i]) //COPIA LINHA ANTERIOR EM AUX 
	{
		aux[i] = (*dst_line)[i];
		i++;
	}
	strfree(dst_line); //LIBERA LINHA (dst = line)
	while ((*add_buff)[j] != '\0')
	{
		aux[i] = (*add_buff)[j];//COPIA BUFFER EM AUX
		(*add_buff)[j] = '\0'; //VAI APAGANDO BUFFER, restante ja foi apagado
		i++;
		j++;
	}
	aux[i] = '\0'; 
	if (!(*dst_line = malloc(size*sizeof(char)))) //aloca com o tamanho novo
	{
		strfree(&aux);
		return (1);
	}
	strcopy(dst_line, &aux, 0);	//COPIA em DTS, o SRC:
	strfree(&aux); //libera p n dar Mleak
	return (0);
}
int creatline(char **buf, char **rest, char **line) //SPLITBUFFER!!!!!int = 0 nao tem resto
{//FATIA BUF ATE PRIMEIRO \n - sem ele!. RESTANTE FICA EM REST - sem o 1o \n
	int i;
	int oneline;

	i = 0;
	oneline = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
	{
	   if ((*buf)[i + 1] != '\0') //AINDA TEM CARACTERE NO BUFFER
	   {
		   strcopy(rest, buf, i + 1); //COPIA EM RESIDUAL apartir do \n
		   while((*buf)[i] != '\0')
		   {	 //zera fim do buffer
			   (*buf)[i] = '\0';
			   i++;
		   }
	   }
	   else
		   (*buf)[i] = '\0';
	   oneline = 1;
	}
	if (ft_strappend(line, buf))
		return (-1);
	return (oneline);
}
