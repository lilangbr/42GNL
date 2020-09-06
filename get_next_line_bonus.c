/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/09/06 15:19:26 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*f_calloc(int size)
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
		f_strcopy(&buff, rest, 0, 0);
		if ((lineresult = f_creatline(&buff, rest, line)))
			return (lineresult);
	}
	while ((ret = read(fd, buff, BUFFER_SIZE) > 0))
		if ((lineresult = f_creatline(&buff, rest, line)))
			return (lineresult);
	if (ret == -1)
	{
		f_strfree(line);
		return (-1);
	}
	if ((lineresult = f_creatline(&buff, rest, line)))
		return (lineresult);
	f_strfree(rest);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*residual[OPEN_MAX];
	char		*buff;
	int			gnl;

	if (line == NULL || fd < 0 || fd >= OPEN_MAX
			|| (read(fd, NULL, 0)) || BUFFER_SIZE < 1
			|| !(buff = f_calloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!(residual[fd]) && !(residual[fd] = f_calloc(BUFFER_SIZE + 1)))
		return (-1);
	gnl = gnl_core(buff, &(residual[fd]), line, fd);
	if (gnl == -1)
		f_strfree(&(residual[fd]));
	f_strfree(&buff);
	buff = NULL;
	return (gnl);
}
