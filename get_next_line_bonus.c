/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:43:07 by zmoussam          #+#    #+#             */
/*   Updated: 2022/03/06 03:02:37 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_filles(int rd, char *rest, int fd, char *buffer)
{
	while (rd != 0 && !ft_strchr(rest, '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
		{	
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		rest = ft_strjoin(rest, buffer);
	}
	return (rest);
}

char	*get_new_line(char *rest)
{
	int		len;
	char	*str;

	len = 0;
	while (rest[len] && rest[len] != '\n')
		len++;
	str = ft_substr(rest, 0, len + 1);
	return (str);
}

char	*get_new_rest(char *rest)
{
	size_t	len;
	char	*str;

	len = 0;
	while (rest[len] && rest[len] != '\n')
		len++;
	str = ft_substr(rest, len + 1, ft_strlen(rest) - len + 1);
	free(rest);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_line;
	static char	*rest[1024];
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rd = 1;
	rest[fd] = read_filles(rd, rest[fd], fd, buffer);
	if (!rest[fd])
		return (NULL);
	if (!rest[fd][0])
	{
		free(rest[fd]);
		free(buffer);
		rest[fd] = NULL;
		return (NULL);
	}
	new_line = get_new_line(rest[fd]);
	rest[fd] = get_new_rest(rest[fd]);
	free(buffer);
	return (new_line);
}
