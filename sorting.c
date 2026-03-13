/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sorting.c                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/13 15:30:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/13 17:40:28 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

t_node	*sort_indices(t_node **list)
{
	t_node	*head;
	t_node	*tmp;

	head = *list;
	tmp = *list;
	printf("%d\n", tmp->next->value);
	while (tmp)
	{
		printf("test\n");
		while ((*list)->next)
		{
			if (tmp->value > (*list)->next->value)
				tmp->sorted_index += 1;
			*list = (*list)->next;
		}
		*list = head;
		printf("%d\n", tmp->sorted_index);
		tmp = tmp->next;
	}
	return (head);
}
