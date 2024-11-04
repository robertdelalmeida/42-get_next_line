/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:41:26 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 12:41:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char	*get_next_line(int fd)
{
	static char		*all_read = NULL;
	char			*buffer;
	char			*line;
	char			*temp;
	size_t			bytes_read;

	if (fd < 0 || (fd > 0 && fd < 3))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!all_read)
	{
		all_read = ft_strdup("");
		if (!all_read)
			return (NULL);
	}
	// ft_buffer();
	bytes_read = 0;
	while (!ft_strchr(all_read, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(all_read);
			all_read = NULL;
			return (NULL);
		}
		buffer[bytes_read + 1] = '\0';
		temp = ft_strjoin(all_read, buffer);
		free(all_read);
		all_read = temp;
	}
	line = ft_strcopy(all_read);
	if (!line)
		return (NULL);
	temp = ft_strdup(all_read + ft_strlen(line));
	free(all_read);
	all_read = temp;
	free(buffer);
	return (line);
}
	// printf("all: %c%c%c\n", all_read[0], all_read[1], all_read[2]);
	// printf("len: %d\n", ft_strlen(line));

char	*ft_strcopy(char *all_read)
{
	char	*line;
	size_t	new_line_pos;
	size_t	i;

	new_line_pos = 0;
	while (all_read[new_line_pos] != '\n' && all_read[new_line_pos] != '\0')
		new_line_pos++;
	line = malloc(new_line_pos + 2);
	i = 0;
	while (i <= new_line_pos)
	{
		line[i] = all_read[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// int main()
// {
// 	char *line;
// 	int fd;
// 	int i = 1;

// 	line = NULL;
// 	fd = open("text.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("chamada %d '%s'\n", i, line);
// 		i++;
// 	}
// 	printf("chamada final %d '%s'\n", i, line);

// 	fd = open("text copy.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("chamada %d '%s'\n", i, line);
// 		i++;
// 	}
// 	printf("chamada final %d '%s'\n", i, line);
// }