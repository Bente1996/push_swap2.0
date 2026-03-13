/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sorting.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/13 15:30:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/13 17:20:25 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

t_node	**sort_indices(t_node **list)
{
	t_node	**head;
	t_node	*tmp;

	head = list;
	tmp = *list;
	printf("%d\n", tmp->value);
	while (tmp)
	{
		printf("test\n");
		while ((*list)->next)
		{
			if (tmp->value > (*list)->next->value)
				tmp->sorted_index += 1;
			*list = (*list)->next;
		}
		list = head;
		printf("%d\n", tmp->sorted_index);
		tmp = tmp->next;
	}
	free (tmp);
	return (head);
}

#include <stdlib.h>

//t_node	*sort_indices(t_node **list)
//{
//	t_node	**tmp;
//
//	printf("head:%p\nnode:%p\n", list, (*list));
//	printf("head:%p\nnode:%d\n\n", *list, (*list)->value);
//
//	tmp = list; //tmp is head
//	while (*tmp) // door hele lijst
//	{
//		while ((*tmp)->next) // zoland er wat staat op volgende node
//		{
//			if ((*tmp)->value > (*tmp)->next->value)
//				(*tmp)->sorted_index += 1;
//			(*tmp) = (*tmp)->next;
//		}
//		printf("head:%p\nnode:%p\n", list, (*list));
//		printf("head:%p\nnode:%d\n", *list, (*list)->value);
//		//(*list) = *list;
//		*tmp = (*tmp)->next;
//	}
//	free (tmp);
//	return (*list);
//}
