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

t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	tmp = NULL;
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
	free (tmp);
	return (new);
}
