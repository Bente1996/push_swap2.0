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
	new->n_index = 0;
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

t_stats	*alloc_stats(t_node **A, t_node **B, int half)
{
	t_stats	*data;
	int	all;

	all = half * 2;
	data = malloc(sizeof(t_stats));
	if (!data)
		return (NULL);
//	data->A = *A;
//	data->B = *B;
	if (!already_sorted(*B) && !already_sorted(*A)) // als stack_a niet gesorteerd
		data->top = 1;
	else
		data->top = 0; // voeg toe aan big_list en bl_two? mss
	data->quarter = half / 2;
	data->lower = --half;
	data->three_quarter = all - (half / 2) - 1;
	data->h = half + 1;
	data->tq = data->three_quarter + 1;
	data->bottom_stack = NULL;
	return (data);
}
