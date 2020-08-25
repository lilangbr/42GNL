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
/*
static int endofline(char *s) //Recebe o buffer
{ //RETORNA POSICAO DO \n
	int pos;

	pos = -1;
	if (!(*s)) //String nula "\o" NAO TEM \n
		return (pos);
	pos = 0;
	while (s[pos] != '\0') //Varre ate achar \n
	{
		if (s[pos] == '\n')
			return (pos);
		pos++;
	}
	if (pos == ft_strlen(s)) //Percorreu sem encontrar
		return (-2);
	else //Nem eh nula, nem tem, nem n tem - portanto !s
		return (-1);
}
*/
static void strcopy(char **dst, char **src, int start)
{ //CONDICAO DST >= SRC!
	int i;
	int j;

	i = 0;
	j = start;
	while ((*src)[j]) //FAZER FUNCAO COPYSTR
	{
		(*dst)[i] = (*src)[j];
		//(*dst)++;//Incremento direto, sem i, j, pois qdo sai do escopo, zera.***
		//(*src)++;
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
		//(*buffer)++;
		i++;
	}
}
static int ft_strappend(char **dst, char **add)// dst = s_main && add = buf
{   //ja existe dst!!!
	//add nao tem /n!!
	size_t size;
	size_t i;//COMO MANDO **S, uso vars q mantenham as strs.***(anotar!)
	size_t j;
	char *aux;
	
	size = ft_strlen(*dst) + ft_strlen(*add) + 1; 
	if (!(aux = malloc(size * sizeof(char)))) //VAI RECEBER A LINHA ANT + BUFF
		return (1);
    i = 0;
	j = 0;
	while ((*dst)[i]) //COPIA LINHA ANTERIOR EM AUX 
	{
		aux[i] = (*dst)[i];
		i++;
	}
	free(*dst); //LIBERA LINHA (dst = line)
	*dst = NULL;
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
		return (1);
	strcopy(dst, &aux, 0);	//COPIA em DTS, o SRC:
	free(aux); //libera p n dar Mleak
	aux = NULL;
	return (0);
}
static int splitbuffer(char **buf, char **rest) //int = 0 nao tem resto
{//FATIA BUF ATE PRIMEIRO \n - sem ele!. RESTANTE FICA EM REST - sem o 1o \n
	int i;
	int j;
	int oneline;

	i = 0;
	j = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\0')
		return (0); //NAO \n, e portanto: NAO TEM RESTO
	//ENTAO EH \n!
	else if ((*buf)[i + 1] != '\0') //AINDA TEM CARACTERE NO BUFFER
	{
		strcopy(rest, buf, i + 1); //COPIA EM RESIDUAL apartir do \n
		zerabuffer(buf, i); //vai zerar o inicio qdo copiar em *line!
		//ja elimina o \n!!! (comeca a partir de i)*********
	}
	else //So tinha \n e nada mais
	{
		zerabuffer(buf, i);//tira o \n fora
	}
	return (1);
}
static void strfree(char **s) //ENTENDER PQ EXISTE A CONDICAO s != NULL no if)
{
	if (s != NULL && *s != NULL) //(*s != NULL || s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}
static int strinit(char **s, int size) //REDUNDANTE?
{
	//if (*s)
	//	strfree(s); //JA ESTAVA INICIALIZADA
	//if (!(*s)) //*s == NULL
	//{
		if (!(*s = malloc(size * sizeof(char)))) 
			return (1); //erro Malloc. Retorna NULL pointer
		(*s)[size - 1] = '\0';
		zerabuffer(s, 0);
		return (0);
	//}
}
int gnl(int fd, char **line)
{
	ssize_t ret;
	static char *residual[5]; //AINDA N VOU MEXER C OPEN_MAX
	//static int count;******************************************
	char **buf;
	//char **rest;
	int oneline;
	char buffer[BUFF_SIZE + 1]; //TESTE
    //char buffer[24] = "oi\nmenina\ntudo\nbem?"; //TESTE
	
	/* inicializacoes 

	if (count == 0)
	{
		buffer[0] = 'o';
		buffer[1] = 'l';
		buffer[2] = 'a';
		buffer[3] = '\n';
		buffer[4] = 't';
		buffer[5] = '
		*/
	buffer[BUFF_SIZE] = '\0';
	oneline = 0;
	//if (!(*line)) //NAO EXISTE LINHA --------------NAO PRECISA TESTAR. TEORICAMENTE N EXISTE!
		if (strinit(line, 1) < 0) //Malloc na qtidade necessaria
			return (-1); //erro na MAlloc
	if (!residual[fd]) //NAO EXISTE RESIDUO PARA ESTE FD
		if (strinit(&(residual[fd]), (BUFF_SIZE + 1)) < 0) //Malloc na qtidade necessaria
			return (-1); //erro na MAlloc
	if (!(buf = malloc(sizeof(char *))))
		return (-1);
	*buf = buffer;
	zerabuffer(buf, 0);

	//if (!(*buf = malloc(BUFF_SIZE*sizeof(char ))))
	//	return (-1);


	/* logica */
	if (residual[fd])
	{ //ja estava sendo trabalhado o residual[fd]
		while (*(residual[fd])) //!= NULL, i.e, existe resto!
		{
			strcopy(buf, &(residual[fd]), 0);
			zerabuffer(&(residual[fd]), 0);
			oneline = splitbuffer(buf, &(residual[fd]));
			if (ft_strappend(line, buf))
				return (-1);
			if (oneline)
				return (1);
		}
	}
	//NAo tem residuo!
	while ((ret = read(fd, *buf, BUFF_SIZE) > 0))
	{
		/* desenvolver */
		oneline = splitbuffer(buf, &(residual[fd]));
		if (ft_strappend(line, buf))
			return (-1);
		if (oneline)
			return (1);
	}
	//ret = 0 -> EOF!
	oneline = splitbuffer(buf, &(residual[fd]));
	if (ft_strappend(line, buf))
		return (-1);
	//if (oneline)
	//	return (1);
	return (0); //EOL ************************************ e se EOL e Uma linha? O que devolve?
}
int main()
{
	char **linemain;
	int fd;
	int gnlret;
	int count;

	fd = open("42", O_RDONLY);
	if (fd == -1)
	{
		printf("File Open Error\n");
		return (1);
	}
	
	//fd = 3; //TIRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
	if (!(linemain = (char **)malloc(1*sizeof(char*)))) //pointer to pointer
			return (1);
	while ((gnlret = gnl(fd, linemain)))
	{
		if (gnlret < 0)
		{
			printf("An error happened in get_next_line!");
			return (1);
		}
		printf("Linha %d: %s\n", count, *linemain);
		count++;
		free(*linemain); //Alocou dentro da GNL
	}
	//residualFDfree(fd); ??????????????? COMO LIBERA O RESIDUO?
	if (close(fd) == -1)
	{
		printf("File Close Error!\n");
		//residualFDfree(fd);
		return (1);
	}
	return (0);
}
