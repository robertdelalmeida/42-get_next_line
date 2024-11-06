/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-fra <rdel-fra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:26 by marvin            #+#    #+#             */
/*   Updated: 2024/11/06 18:25:58 by rdel-fra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*all_read[1024];
	char			*buffer;
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (all_read[fd] == NULL)
		all_read[fd] = ft_strdup("");
	buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!buffer)
		return (free(all_read[fd]), all_read[fd] = NULL);
	all_read[fd] = ft_get_buffer(fd, &all_read[fd][0], buffer);
	if (all_read[fd] == NULL)
		return (NULL);
	line = ft_getline(&all_read[fd][0]);
	temp = ft_strdup(&all_read[fd][0] + ft_strlen(line));
	free(all_read[fd]);
	all_read[fd] = temp;
	if (!line)
		return (free(line), free(all_read[fd]), all_read[fd] = NULL);
	return (line);
}

char	*ft_get_buffer(int fd, char *all_read, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (ft_strchr(all_read, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || (!*all_read && !*buffer && bytes_read == 0))
			return (free(all_read), free(buffer), all_read = NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(all_read, buffer);
		free(all_read);
		all_read = temp;
	}
	free(buffer);
	return (all_read);
}

char	*ft_getline(char *all_read)
{
	char	*line;
	size_t	new_line_pos;
	size_t	i;

	new_line_pos = 0;
	while (all_read[new_line_pos] != '\n' && all_read[new_line_pos] != '\0')
		new_line_pos++;
	line = ft_calloc((new_line_pos + 2), 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i, all_read[i] != '\0' && all_read[i] != '\n')
		line[i] = all_read[i];
	if (all_read[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	char *line;
// 	int fd1;
// 	int fd2;
// 	int i = 1;
// 	int j = 1;
// 	printf("BUFFER_SIZE:%d\n", BUFFER_SIZE);

// 	printf("\nFIRST TEST\n");
// 	fd1 = open("text copy.txt", O_RDONLY);
// 	while (i < 3)
// 	{
// 		line = get_next_line(fd1);
// 		printf("call %d is:%s", i, line);
// 		free(line);
// 		i++;
// 	}

// 	printf("\nSECOND TEST\n");
// 	fd2 = open("text jump line.txt", O_RDONLY);
// 	while ((line = get_next_line(fd2)) != NULL && i < 4)
// 	{
// 		line = get_next_line(fd2);
// 		if (ft_strchr(line, '\n') == 0)
// 			printf("call %d is:%s\n", j, line);
// 		else
// 			printf("call %d is:%s", j, line);
// 		free(line);
// 		j++;
// 	}
// 	printf("final call %d is:%s\n", j, line);

// 	printf("\nFIRST TEST AGAIN\n");
// 	while ((line = get_next_line(fd1)) != NULL)
// 	{
// 		printf("call %d is:%s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	printf("\nfinal call %d is:%s\n", i, line);
// 	close(fd1);

// 	printf("\nSECOND TEST AGAIN\n");
// 	while ((line = get_next_line(fd2)) != NULL)
// 	{
// 		if (ft_strchr(line, '\n') == 0)
// 			printf("call %d is:%s\n", j, line);
// 		else
// 			printf("call %d is:%s", j, line);
// 		free(line);
// 		j++;
// 	}
// 	printf("final call %d is:%s\n", j, line);
// 	close(fd2);

// 	printf("\nTHIRD TEST\n");
// 	fd1 = -1;
// 	printf("negative fd:%s\n", get_next_line(fd1));

// 	printf("\nFOURTH TEST\n");
// 	fd1 = open("text copy.txt", O_RDONLY);
// 	close(fd1);
// 	printf("close fd:%s\n", get_next_line(fd1));
// }