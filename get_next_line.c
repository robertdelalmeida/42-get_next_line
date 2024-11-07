/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-fra <rdel-fra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:26 by marvin            #+#    #+#             */
/*   Updated: 2024/11/07 14:20:56 by rdel-fra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*all_read;
	char			*buffer;
	char			*line;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!all_read)
		all_read = ft_strdup("");
	buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!buffer)
		return (free(all_read), all_read = NULL);
	all_read = ft_get_buffer(fd, all_read, buffer);
	if (all_read == NULL)
		return (NULL);
	line = ft_getline(all_read);
	temp = ft_strdup(all_read + ft_strlen(line));
	free(all_read);
	all_read = temp;
	if (!line)
		return (free(line), free(all_read), all_read = NULL);
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
// 	// char *line;
// 	// int fd;
// 	// // int i = 1;
// 	// printf("BUFFER_SIZE:%d\n", BUFFER_SIZE);
// 	// // echo -n "message" > input.txt
// 	// printf("stdin: %s\n", get_next_line(fd));
// 	// printf("stdin: %s\n", get_next_line(fd));
// 	// printf("\nFIRST TEST\n");
// 	// fd = open(".txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("call %d is:%s", i, line);
// 	// 	free(line);
// 	// 	i++;
// 	// }
// 	// printf("\nfinal call %d is:%s\n", i, line);
// 	// close (fd);
// 	// printf("\nSECOND TEST (with empty lines)\n");
// 	// i = 1;
// 	// fd = open(".txt", O_RDONLY);
// 	// while ((line = get_next_line(fd)) != NULL)
// 	// {
// 	// 	if (ft_strchr(line, '\n') == 0)
// 	// 		printf("call %d is:%s\n", i, line);
// 	// 	else
// 	// 		printf("call %d is:%s", i, line);
// 	// 	free(line);
// 	// 	i++;
// 	// }
// 	// printf("final call %d is:%s\n", i, line);
// 	// close(fd);
// 	// printf("\nTHIRD TEST\n");
// 	// printf("negative fd:%s\n", get_next_line(-1));
// 	// printf("\nFOURTH TEST\n");
// 	// fd = open(".txt", O_RDONLY);
// 	// close(fd);
// 	// printf("close fd (invalid):%s\n", get_next_line(fd));
// }