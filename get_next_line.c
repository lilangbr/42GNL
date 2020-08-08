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
static int endofline(char *s) //Recebe o buffer
{
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
static void ft_strappend(char **dst, char **add)// dst = s_main && add = buf
{
	size_t size;
	size_t i;
	size_t j;
	char *aux;
	char resto[24];

	*dst = malloc(1*sizeof(char)); //gnl
	**dst = '\0'; 				//gnl ..... EH A LINHA!
	if (endofline(*add) < 0) //Nao tem \n no buffer
		size = ft_strlen(*dst) + ft_strlen(*add) + 1; //pega todo o buffer
	else
		size = ft_strlen(*dst) + endofline(*add) + 1; //pega ate \n
	aux = malloc(size * sizeof(char)); //armazenamento temporario
    i = 0;
	j = 0;
	while (*dst[i]) //se houver itens na linha, copia 
	{
		aux[i] = *dst[i];
		i++;
	}
	while (**add != '\0' && **add != '\n') //copia buffer ate \n ou at o fim
	{
		aux[i] = **add;
		i++;
		j++;
		(*add)++;
	}
	aux[i] = '\0'; 
	(*add)++; //Atualiza posicao no buffer para a casa depois do \n
	free(*dst); //libera linha anterior (pedaco anterior)
	*dst = malloc(size*sizeof(char)); //aloca com o tamanho novo
	//copia ate o final (\0)
	i = 0;
	while (aux[i]) //FAZER FUNCAO COPYSTR
	{
		(*dst)[i] = aux[i];
		i++;
	}
	(*dst)[i] = '\0';
	free(aux); //libera p n dar Mleak
	//(*add)++; JA fiz na funcao append
	i = 0;
	while ((*add)[i]) //FAZER FUNCAO COPYSTR
	{
		resto[i] = (*add)[i];
		i++;
	}
	resto[i] = '\0';
	printf("----------------------------\n");
	printf("REMANESCENTE: %s\n", resto);
	printf("----------------------------\n");
}
int main()
{
	char **s_main;
	char **buf;
    char buffer[24] = "oi\nmenina\ntudo\nbem?";
	char **final;

	printf("----------------------------\n");
	printf("Conteudo buffer: 'oi\\nmenina,\\ntudo\\nbem?'\n");
	s_main = malloc(1*sizeof(char*)); //pointer to pointer
	buf = malloc(1*sizeof(char*)); //pointer to pointer
	*buf = buffer; //pointer to string
	ft_strappend(s_main, buf);//send pointers to pointers
	final = s_main;
	printf("LINHA: %s\n", *final);
	printf("----------------------------\n");
	return 0;
}
