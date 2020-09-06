/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/09/06 15:19:26 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_calloc(int size)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc((size + 1) * sizeof(char));
	while (i < size)
		s[i++] = '\0';
	return (s);
}

static int	gnl_core(char *buff, char **rest, char **line, int fd)
{
	ssize_t	ret;
	int		lineresult;

	if (!(*line = malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	while (**rest)
	{
		strcopy(&buff, rest, 0, 0);
		if ((lineresult = creatline(&buff, rest, line)))
			return (lineresult);
	}
	while ((ret = read(fd, buff, BUFFER_SIZE) > 0))
		if ((lineresult = creatline(&buff, rest, line)))
			return (lineresult);
	if (ret == -1)
	{
		strfree(line);
		return (-1);
	}
	if ((lineresult = creatline(&buff, rest, line)))
		return (lineresult);
	strfree(rest);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*residual;
	char		*buff;
	int			gnl;

	if (line == NULL || fd < 0 || fd >= OPEN_MAX
			|| (read(fd, NULL, 0)) || BUFFER_SIZE < 1
			|| !(buff = ft_calloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!residual && !(residual = ft_calloc(BUFFER_SIZE + 1)))
		return (-1);
	gnl = gnl_core(buff, &residual, line, fd);
	if (gnl == -1)
		strfree(&residual);
	strfree(&buff);
	buff = NULL;
	return (gnl);
}
