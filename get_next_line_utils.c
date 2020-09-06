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

size_t	ft_strlen(const char *s)
{
	if (!s)
		return (-1);
	else if (*s == '\0')
		return (0);
	return (ft_strlen(++s) + 1);
}

void	f_strfree(char **s)
{
	if (s != NULL && *s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}

void	f_strcopy(char **dst, char **src, int start_src, int start_dst)
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

int		f_strjoin(char **dst_line, char **add_buff)
{
	size_t	size;
	size_t	i;
	char	*aux;

	size = ft_strlen(*dst_line) + ft_strlen(*add_buff) + 1;
	if (!(aux = malloc(size * sizeof(char))))
		return (1);
	i = ft_strlen(*dst_line);
	f_strcopy(&aux, dst_line, 0, 0);
	f_strfree(dst_line);
	f_strcopy(&aux, add_buff, 0, i);
	if (!(*dst_line = malloc(size * sizeof(char))))
	{
		f_strfree(&aux);
		return (1);
	}
	f_strcopy(dst_line, &aux, 0, 0);
	f_strfree(&aux);
	return (0);
}

int		f_creatline(char **buf, char **rest, char **line)
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
			f_strcopy(rest, buf, i + 1, 0);
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
	if (f_strjoin(line, buf))
		return (-1);
	return (oneline);
}
