/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:54:30 by rhmimchi          #+#    #+#             */
/*   Updated: 2023/11/26 02:04:43 by rhmimchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_line(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *get_first_line(char *str)
{
	int i = 0;
	char *ret;

	while (str[i] != '\n' && str[i] != '\0')
		i++;

	ret = malloc(sizeof(char) * (i + 2));
	if (ret == NULL)
		return (NULL);

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\n';
	ret[i + 1] = '\0';
	return (ret);
}

void	remove_first_line(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		buffer[0] = '\0';
	else
	{
		j = 0;
		while (buffer[i] != '\0')
		{
			buffer[j] = buffer[i];
			j++;
			i++;
		}
		buffer[j] = '\0'; 
	}
}

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1];
    char *result = NULL;
	char *final = NULL;
    int readvalue;
	
    if (buffer[0] == '\0')
	{ 
        readvalue = read(fd, buffer, BUFFER_SIZE);
        if (readvalue <= 0)
            return NULL;
        buffer[readvalue] = '\0';
    }

    if (check_line(buffer) == 1)
	{
        result = get_first_line(buffer);
        remove_first_line(buffer);
        return result;
    }

    result = ft_strdup(buffer);
	

    while ((readvalue = read(fd, buffer, BUFFER_SIZE)) > 0) 
	{
        buffer[readvalue] = '\0';
        free(result);
        result = ft_strjoin(result, buffer);

        if (check_line(buffer) == 1)
		{ 
            remove_first_line(buffer);
            break;
        }
    }
	final = get_first_line(result);
	if (readvalue == 0)
	{
		buffer[0] = '\0';
	}
	free(result);
    return (final);
}
/*
int main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	int i = 0;
	printf("=================================\n");
	while (i < 7)
	{
		printf("%s", get_next_line(fd));
		i++;
	}
	close(fd);
}
*/
