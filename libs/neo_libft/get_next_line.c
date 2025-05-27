/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:57:18 by mely-pan          #+#    #+#             */
/*   Updated: 2025/02/15 12:57:19 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			b_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buff[0] == '\0')
		{
			b_read = read(fd, buff, BUFFER_SIZE);
			if (b_read < 0 && line)
				return (free(line), NULL);
			if (b_read == 0 || (b_read < 0 && !line))
				return (line);
			buff[b_read] = '\0';
		}
		line = ft_strjoin_gnl(line, buff);
		if (!line)
			return (NULL);
		if (cut_remaining(buff))
			break ;
	}
	return (line);
}
