/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 20:46:03 by ebresser          #+#    #+#             */
/*   Updated: 2020/08/07 20:46:56 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	while ((gnlret = get_next_line(fd, linemain))) 
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
