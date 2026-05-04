/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   nodes.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:15:43 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:24:58 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include <stdlib.h>

t_node	*new_node(int value, int index)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->sorted_index = 0;
	new->next = NULL;
	return (new);
}

#include <stdio.h>

t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	//if (is_duplicate(*head, value))
	//	return (NULL);
	new = new_node(value, index);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_stats	*alloc_stats(t_node **stack_a, t_node **stack_b, int half)
{
	t_stats	*data;

	data = malloc(sizeof(t_stats));
	if (!data)
		return (NULL);
	data->stack_a = *stack_a; // data->stack_a = head
	data->stack_b = *stack_b;
	data->whole = half * 2;
	data->quarter = half / 2;
	data->three_quarter = data->whole - data->quarter;
	data->tq = data->three_quarter + 1;
	data->h = half + 1;
	data->swap = 0;
	data->swap_rot = 0;
	data->lower = half + 1;
	data->bottom = 0;
	data->bottom_stack = NULL;
	return (data);
}
