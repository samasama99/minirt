/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 09:36:31 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/10 09:39:19 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*get_heap(t_list **command)
{
	static t_list	**heap;

	if (command)
		heap = command;
	return (*heap);
}

void	*ft_malloc(size_t size)
{
	static t_list	*heap;
	void			*mem;

	if (heap == NULL)
		get_heap(&heap);
	mem = (void *)malloc(size);
	if (mem == NULL)
	{
		perror("Error:");
		exit(1);
	}
	ft_lstadd_back(&heap, ft_lstnew(mem));
	return (mem);
}

void	ft_free(void)
{
	t_list	*head;
	t_list	*next;

	head = get_heap(NULL);
	while (head)
	{
		free(head->content);
		head->content = NULL;
		next = head->next;
		free(head);
		head = next;
	}
}
