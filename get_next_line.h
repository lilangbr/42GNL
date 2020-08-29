/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h> //READ
# include <sys/uio.h> //READ
# include <fcntl.h> //OPEN
# include <stdio.h> //PRINTF
# include <stdlib.h> //MALLOC
# include <unistd.h> //CLOSE

int		ft_strlen(const char *s);
void	strfree(char **s);
void	strcopy(char **dst, char **src, int start);
void	zerabuffer(char **buffer, int start);
int		ft_strappend(char **dst, char **add);
int		splitbuffer(char **buf, char **rest);
int		get_next_line(int fd, char **line);

#endif


