/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:06:37 by htrindad          #+#    #+#             */
/*   Updated: 2024/04/18 20:01:55 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		num;
	int		neg;
	size_t	i;

	i = 0;
	neg = 1;
	num = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			neg = -1;
		i++;
	}
	while (ft_isdigit((int)nptr[i]))
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	return (num * neg);
}
