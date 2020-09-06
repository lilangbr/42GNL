/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/09/06 18:03:51 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *s)
{
	if (!s)
		return (-1);
	else if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}

void	strfree(char **s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

void	strcopy(char **dst, char **src, int start_src, int start_dst)
{
	int i;
	int j;

	i = start_dst;
	j = start_src;
	while ((*src)[j])
	{
		(*dst)[i] = (*src)[j];
		(*src)[j] = '\0';
		i++;
		j++;
	}
	(*dst)[i] = '\0';
}

int		ft_strappend(char **dst_line, char **add_buff)
{
	size_t	size;
	size_t	i;
	char	*aux;

	size = ft_strlen(*dst_line) + ft_strlen(*add_buff) + 1;
	if (!(aux = malloc(size * sizeof(char))))
		return (1);
	i = ft_strlen(*dst_line);
	strcopy(&aux, dst_line, 0, 0);
	strfree(dst_line);
	strcopy(&aux, add_buff, 0, i);
	if (!(*dst_line = malloc(size * sizeof(char))))
	{
		strfree(&aux);
		return (1);
	}
	strcopy(dst_line, &aux, 0, 0);
	strfree(&aux);
	return (0);
}

int		creatline(char **buf, char **rest, char **line)
{
	int i;
	int oneline;

	i = 0;
	oneline = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
	{
		if ((*buf)[i + 1] != '\0')
		{
			strcopy(rest, buf, i + 1, 0);
			while ((*buf)[i] != '\0')
			{
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
