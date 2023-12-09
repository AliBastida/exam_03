/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastida <abastida@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:56:11 by abastida          #+#    #+#             */
/*   Updated: 2023/12/07 17:32:11 by abastida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int is_line(char *buffer)
{
	int i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return(0);
}

char *strjoin(char *s1, char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);
	int i = 0;
	int j = 0;
	char *line = malloc(sizeof(char) * len1 + len2 + 1);
	if (!line)
		return (NULL);
	if (s1)
	{
		while (s1[i])
			line[j++] = s1[i++];
		free(s1);
	}
	i = 0;
	while(s2[i])
		line[j++] = s2[i++];
	line[j] = '\0';
	return (line);
}

char *push_line(char *resto)
{
	int i = 0;
	char *line;
	
	while(resto[i] && resto[i] !='\n')
		i++;
	if (resto[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if(!line)
		return (line);
	i = 0;
	while (resto[i] && resto[i] !='\n')
	{
		line[i] = resto[i];
		i++;
	}
	if (resto[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
		return(line);
	}
	else
		line[i] = '\0';
	return(line);
}

char *cut_line(char *resto)
{
	int i = 0;
	int j = 0;
	char *new_resto;
	while (resto[i] && resto[i] != '\n')
		i++;
	if(!resto[i])
	{
		free(resto);
		return(NULL);
	}
	new_resto = malloc(sizeof(char) * ft_strlen(resto) - i + 1);
	if (!new_resto)
		return(NULL);
	i++;
	while (resto[i])
		new_resto[j++] = resto[i++];
	free(resto);
	new_resto[j] = '\0';
	return (new_resto);
}

char *get_next_line(int fd)
{
	static char *resto = NULL;
	char *line = NULL;
	char buffer[BUFFER_SIZE + 1] = {0};
	int rd = 1;
	
	while (!is_line(buffer) && rd != 0)
	{
		if ((rd = read(fd, buffer, BUFFER_SIZE)) <0)
		{
			if (resto)
			{
				free(resto);
				resto = NULL;
			}
			return (NULL);
		}
		buffer[rd] = '\0';
		resto = strjoin(resto, buffer);
	}
	line = push_line(resto);
	resto = cut_line(resto);
	if(!line || line[0] == '\0')
	{
		free(line);
		return(NULL);
	}
	return(line);
}
