/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:50:33 by htrindad          #+#    #+#             */
/*   Updated: 2024/04/13 15:50:47 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*td;
	unsigned char	*ts;

	if (!n || dest == src)
		return (dest);
	td = dest;
	ts = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		td[i] = ts[i];
		i++;
	}
	return (dest);
}
