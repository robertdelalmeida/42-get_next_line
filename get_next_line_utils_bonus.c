/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-fra <rdel-fra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:07:09 by marvin            #+#    #+#             */
/*   Updated: 2024/11/06 18:27:37 by rdel-fra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			size_max;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	size_max = -1;
	if (size != 0 && (nmemb >= size_max / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)&ptr[0]);
}
