/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:27:24 by htrindad          #+#    #+#             */
/*   Updated: 2024/05/02 14:22:21 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*nn;

	if (!lst || !f || !del)
		return (NULL);
	nlst = ft_lstnew(f(lst->content));
	if (!nlst)
		return (NULL);
	nn = nlst;
	lst = lst->next;
	while (lst)
	{
		nlst->next = ft_lstnew(f(lst->content));
		if (!nlst->next)
		{
			ft_lstclear(&nn, del);
			return (0);
		}
		nlst = nlst->next;
		lst = lst->next;
	}
	nlst->next = NULL;
	return (nn);
}
