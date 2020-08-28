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

#include <sys/types.h> //READ
//#include <sys/stat.h>
#include <sys/uio.h> //READ
#include <fcntl.h> //OPEN
#include <stdio.h> //PRINTF
#include <stdlib.h> //MALLOC
#include <unistd.h> //CLOSE
#include <limits.h> //OPEN_MAX = 10240!

static int ft_strlen(const char *s)
{
	if (!s)
		return (-1);
	else if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}
static void strfree(char **s) 
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

static void strcopy(char **dst, char **src, int start)
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
static void zerabuffer(char **buffer, int start)
{
	int i;

	i = start;
	while ((*buffer)[i])
	{
		(*buffer)[i] = '\0';
		i++;
	}
}
static int ft_strappend(char **dst, char **add)
{  
	//add nao tem /n!!
	size_t size;
	size_t i;
	size_t j;
	char *aux;
	
	size = ft_strlen(*dst) + ft_strlen(*add) + 1; 
	if (!(aux = malloc(size * sizeof(char)))) 
		return (1);
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
	zerabuffer(add, 0);//LIBERA BUFF
	//ATE P EFEITO DE CONTROLE(se esta zerado eh pq foi cpy)
	if (!(*dst = malloc(size*sizeof(char)))) //aloca com o tamanho novo
	{
		strfree(&aux);
		return (1);
	}
	strcopy(dst, &aux, 0);	//COPIA em DTS, o SRC:
	strfree(&aux); //libera p n dar Mleak
	return (0);
}
static int splitbuffer(char **buf, char **rest) //int = 0 nao tem resto
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
		zerabuffer(buf, i); //vai zerar o inicio qdo copiar em *line!
		//ja elimina o \n!!! (comeca a partir de i)*********
	}
	else //So tinha \n e nada mais
		zerabuffer(buf, i);//tira o \n fora
	oneline = 1;
	return (oneline);
}
static int strinit(char **s, int size) //REDUNDANTE?
{
	if (!(*s = malloc(size * sizeof(char)))) 
		return (1); //erro Malloc. Retorna NULL pointer
	(*s)[size - 1] = '\0';
	zerabuffer(s, 0);
	return (0);
}
int gnl(int fd, char **line)
{
	ssize_t ret;
	static char *residual[5]; //AINDA N VOU MEXER C OPEN_MAX
	char **buf;
	int oneline;
	char buffer[BUFFER_SIZE + 1]; //TESTE
	
	/* inicializacoes */
	buffer[BUFFER_SIZE] = '\0';
	oneline = 0;
	if (strinit(line, 1) < 0) //Malloc na qtidade necessaria
		return (-1); //erro na MAlloc
	if (!residual[fd]) //NAO EXISTE RESIDUO PARA ESTE FD
		if (strinit(&(residual[fd]), (BUFFER_SIZE + 1)) < 0) //Malloc na qtidade necessaria
			return (-1); //erro na MAlloc
	if (!(buf = malloc(sizeof(char *))))
	{
		strfree(line);
		strfree(&residual[fd]);
		return (-1);
	}
	*buf = buffer;
	zerabuffer(buf, 0);
	/* logica */
	if (residual[fd])
	{ //ja estava sendo trabalhado o residual[fd]
		while (*(residual[fd])) //!= NULL, i.e, existe resto!
		{
			strcopy(buf, &(residual[fd]), 0);
			zerabuffer(&(residual[fd]), 0);
			oneline = splitbuffer(buf, &(residual[fd]));
			if (ft_strappend(line, buf)) //ERRO!
			{
				*buf = NULL; //strfree(buf); -> Nao posso fazer pois BUFFER N foi alocado p ser liberado
				free(buf);
				buf = NULL;
				strfree(&(residual[fd]));
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
		oneline = splitbuffer(buf, &(residual[fd]));
		if (ft_strappend(line, buf))
		{
			*buf = NULL; //strfree(buf);
			free(buf);
			buf = NULL;
			strfree(&(residual[fd]));
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
	oneline = splitbuffer(buf, &(residual[fd]));
	//if (*buf) //EXISTE LINHA!!!
	//	oneline = 1;
	if (ft_strappend(line, buf))
	{
		*buf = NULL; //strfree(buf);
		free(buf);
		buf = NULL;
		strfree(&(residual[fd]));
		//strfree(line);
		return (-1);
	}
	//if (oneline)
	//	return (1);
	strfree(&(residual[fd]));
	//free(*buf); //************************************
	*buf = NULL;
	free(buf);
	buf = NULL;
	//strfree(line);
	return (0); //EOL ************************************ e se EOL e Uma linha? O que devolve?
}
int main()
{
	char **linemain;
	int fd;
	int gnlret;

	fd = open("42", O_RDONLY);
	if (fd == -1)
	{
		printf("File Open Error\n");
		return (1);
	}
	
	if (!(linemain = (char **)malloc(1*sizeof(char*)))) //pointer to pointer
			return (1);
	while ((gnlret = gnl(fd, linemain))) 
	{
		if (gnlret < 0)
		{
			printf("An error happened in get_next_line!");
			free(linemain);
			linemain = NULL;

			return (1);
		}
		printf("%s\n", *linemain);
		strfree(linemain);
	}
	printf("%s", *linemain);
	strfree(linemain);
	if (close(fd) == -1)
	{
		printf("File Close Error!\n");
		free(linemain);
		linemain = NULL;
		return (1);
	}
	free(linemain);
	linemain = NULL;
	return (0);
}
