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

t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	if (is_duplicate(*head, value))
		return (NULL);
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

t_stats	init_stats(int half)
{
	t_stats	data;
	int		all;

	data = (t_stats){0};
	all = half * 2;
	data.quarter = half / 2;
	data.lower = --half;
	data.three_quarter = all - (half / 2) - 1;
	data.h = half;
	data.tq = data.three_quarter + 1;
	data.bottom_stack = NULL;
	return (data);
}

t_text	*create_node(const char *text)
{
	t_text *const	new_node = malloc(1 * sizeof(t_text));

	if (new_node)
	{
		new_node->text = text;
		new_node->next = 0;
	}
	return (new_node);
}

void	append_text(t_text **head, const char *op)
{
	t_text	*last;
	t_text	*before_last;

	if (!*head)
	{
		*head = create_node(op);
		return ;
	}
	last = *head;
	before_last = *head;
	while (last->next)
	{
		before_last = last;
		last = last->next;
	}
	if (!check_rotate(before_last, last, op)
		&& !check_r_rotate(before_last, last, op)
		&& !check_r_rotate(before_last, last, op)
		&& !check_swap(before_last, last, op)
		&& !check_push(before_last, last, op))
		last->next = create_node(op);
}
