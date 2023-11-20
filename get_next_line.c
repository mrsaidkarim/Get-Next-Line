/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:41:26 by skarim            #+#    #+#             */
/*   Updated: 2023/11/20 18:57:01 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *first_res)
{
	char	*buf;
	int		read_bytes;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(first_res, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		first_res = ft_strjoin(first_res, buf);
	}
	free(buf);
	return (first_res);
}

char	*ft_get_line(char *str)
{
	int		len;
	char	*line;
	int		i;

	len = 0;
	if (!str[len])
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len])
		len++;
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_rest(char *str)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!rest)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	i++;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_read_file(fd, res);
	if (!tmp)
	{
		if (res)
			free(res);
		res = NULL;
		return (NULL);
	}
	res = tmp;
	line = ft_get_line(res);
	res = ft_get_rest(res);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char	*line;
	int		fd1;
	int		fd2;

	fd1 = open("text.txt", O_RDONLY);
	fd2 = open("t.txt", O_RDONLY);
	if(fd2 < 0 || fd1 < 0)
	{
		perror("error opening file");
		return (1);
	}
	printf("-------file1-------\n");
	line = get_next_line(fd1);
	printf("%s", line);
	free(line);
	printf("-------file2-------\n");
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	printf("-------file1-------\n");
	line = get_next_line(fd1);
	printf("%s", line);
	free(line);
	printf("-------file2-------\n");
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	return (0);
}