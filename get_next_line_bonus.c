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

static char    *ft_calloc(int size)
{
	char    *s;
	int     i;
	
	i = 0;
	s = malloc((size + 1) * sizeof(char));
	while (i < size)
		s[i++] = '\0';
	return (s);
}
static int gnl_core(char *buff, char **rest, char **line, int fd)
{
	ssize_t ret;
	int lineresult;

	if (!(*line = malloc(1*sizeof(char))))
		return (-1);
	**line = '\0';	
	while (**rest) //!= NULL, i.e, existe resto!
	{
		strcopy(&buff, rest, 0);
		if ((lineresult = creatline(&buff, rest, line)))// splitbuffer(&buff, rest);
			return(lineresult);
	}//NAo tem residuo!
	while ((ret = read(fd, buff, BUFFER_SIZE) > 0))
		if ((lineresult = creatline(&buff, rest, line)))// splitbuffer(&buff, rest);
			return(lineresult);
	if (ret == -1)
	{
		strfree(line);
		return (-1);
	}//ret = 0 -> EOF!
	if ((lineresult = creatline(&buff, rest, line)))// splitbuffer(&buff, rest);
		return(lineresult);
	strfree(rest);
	return (0); //EOL ******** e se EOL e Uma linha? O que devolve?
}
int get_next_line(int fd, char **line)
{
	static char *residual[OPEN_MAX]; 
	char *buff;
	int gnl;
	
	if (line == NULL || fd < 0 || fd >= OPEN_MAX || (read(fd, NULL, 0)) || BUFFER_SIZE < 1 || !(buff = ft_calloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!(residual[fd]) && !(residual[fd] = ft_calloc(BUFFER_SIZE + 1)))
		return (-1);
	gnl = gnl_core(buff, &(residual[fd]), line, fd);
	if (gnl == -1)
		strfree(&(residual[fd]));
	strfree(&buff);
	buff = NULL;
	return (gnl);
}
