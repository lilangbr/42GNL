/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

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
		i++;
		j++;
	}
	(*dst)[i] = '\0';
}
void zerabuffer(char **buffer, int start, size_t size)
{
	size_t i;

	i = start;
	if ( buffer != NULL && *buffer != NULL)
	{
		//while ((*buffer)[i]) 
		while (i < size) //ft_strlen(*buffer)) 
		{
			(*buffer)[i] = '\0';
			i++;
		}
	}
}
int ft_strappend(char **dst, char **add) //ESTA FICANDO RESTOOOOOO
{  
	//add nao tem /n!!
	size_t size;
	size_t i;
	size_t j;
	char *aux;
	
	size = ft_strlen(*dst) + ft_strlen(*add) + 1; 
	if (!(aux = malloc(size * sizeof(char)))) 
		return (1);
	zerabuffer(&aux, 0, size);
    i = 0;
	j = 0;
	while ((*dst)[i]) //COPIA LINHA ANTERIOR EM AUX 
	{
		aux[i] = (*dst)[i];
		i++;
	}
	strfree(dst); //LIBERA LINHA (dst = line)
	while ((*add)[j] != '\0')
	{
		aux[i] = (*add)[j];//COPIA ANEXO EM AUX
		i++;
		j++;
	}
	aux[i] = '\0'; 
	zerabuffer(add, 0, BUFFER_SIZE + 1);//LIBERA BUFF
	//ATE P EFEITO DE CONTROLE(se esta zerado eh pq foi cpy)
	if (!(*dst = malloc(size*sizeof(char)))) //aloca com o tamanho novo
	{
		strfree(&aux);
		return (1);
	}
	zerabuffer(dst, 0, size); //-----02set--esta ficando resto!!!!!!!!! ***************!!!!
	strcopy(dst, &aux, 0);	//COPIA em DTS, o SRC:
	strfree(&aux); //libera p n dar Mleak
	return (0);
}
int splitbuffer(char **buf, char **rest) //int = 0 nao tem resto
{//FATIA BUF ATE PRIMEIRO \n - sem ele!. RESTANTE FICA EM REST - sem o 1o \n
	int i;
	int j;
	int oneline;

	i = 0;
	j = 0;
	oneline = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\0')
			return (oneline); 
	//ENTAO EH \n!
	else if ((*buf)[i + 1] != '\0') //AINDA TEM CARACTERE NO BUFFER
	{
		strcopy(rest, buf, i + 1); //COPIA EM RESIDUAL apartir do \n
		zerabuffer(buf, i, BUFFER_SIZE + 1); //vai zerar o inicio qdo copiar em *line!
		//ja elimina o \n!!! (comeca a partir de i)*********
	}
	else //So tinha \n e nada mais
		zerabuffer(buf, i, BUFFER_SIZE + 1);//tira o \n fora
	oneline = 1;
	return (oneline);
}
