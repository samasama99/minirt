/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:29:12 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/16 23:23:08 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	temp = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{	
		current = ft_lstnew (f(lst->content));
		if (current == 0)
		{
			ft_lstclear (&temp, del);
			return (0);
		}
		ft_lstadd_back (&temp, current);
		lst = lst->next;
	}	
	return (temp);
}
