/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:33:21 by htrindad          #+#    #+#             */
/*   Updated: 2024/04/16 20:13:17 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*sc;

	sc = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (sc == NULL)
		return (NULL);
	ft_memcpy(sc, s, ft_strlen(s));
	return (sc);
}
