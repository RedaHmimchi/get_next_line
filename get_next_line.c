/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhmimchi <rhmimchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:54:30 by rhmimchi          #+#    #+#             */
/*   Updated: 2023/11/23 01:45:21 by rhmimchi         ###   ########.fr       */
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

char *check_first(char *str)
{
	int i = 0;
	char *ret;

	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}

	ret = malloc(sizeof(char) * (i + 1)); // Allocate memory for the line
	if (ret == NULL)
		return (NULL);

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	remove_first_line(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
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
	static char *buffer;
	char *result = NULL;
	int readvalue;
	char *newresult;
	
	if (buffer != NULL)
	{
		if (check_line(buffer) == 1)
		{
			result = check_first(buffer);
			remove_first_line(buffer);
			return result;
		}
		else
		{
			result = ft_strdup(buffer);
			free(buffer);
			buffer = NULL;
		}
	}

	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return NULL;
		
	}

	while (1)
	{
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue <= 0)
			break;
		buffer[readvalue] = '\0';
		newresult = ft_strjoin(result, check_first(buffer));
		if (newresult == NULL)
		{
			free(result);
			return NULL;
		}
		free(result);
		result = ft_strdup(newresult);
		free(newresult);
		remove_first_line(buffer);
		if (check_line(buffer) == 1)
			break ;
	}
	return result;
}

int main()
{
	int fd;

	fd = open("text.txt", O_RDONLY);
	int i = 0;
	printf("=================================\n");
	//get_next_line(fd);
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	while (i < 6)
	{
		printf("%s\n", get_next_line(fd));
		i++;
	}
	printf("=================================\n");
}
