/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:13:47 by htrindad          #+#    #+#             */
/*   Updated: 2024/04/21 17:47:25 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_intlen(int n)
{
	int	count;

	count = n < 0;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*ft_ol(int n)
{
	char	*num;

	num = malloc(sizeof(char) * 2);
	if (!num)
		return (num);
	num[1] = 0;
	num[0] = n + 48;
	return (num);
}

char	*ft_itoa(int n)
{
	int		sig;
	int		nlen;
	char	*num;

	sig = n < 0;
	nlen = ft_intlen(n);
	if (nlen < 2)
		return (ft_ol(n));
	num = malloc(sizeof(char) * (nlen + 1));
	if (!num)
		return (num);
	num[nlen] = 0;
	if (sig)
	{
		*num = '-';
		num[--nlen] = -(n % 10) + 48;
		n = -(n / 10);
	}
	while (nlen-- - sig)
	{
		num[nlen] = n % 10 + 48;
		n /= 10;
	}
	return (num);
}
