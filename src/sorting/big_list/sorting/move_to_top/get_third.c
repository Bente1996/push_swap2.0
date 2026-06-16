/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   lowering_utils.c                                        :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:41:40 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:47 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	get_third(t_stats *data, t_node **a)
{
	rra(a);
	sa(a);
	ra(a);
	sa(a);
	data->bottom_stack = find_bottom(*a);
	if ((*a)->n_index == (*a)->next->n_index - 1) // check if bottom fits too
		two_correct(data, a);
	else
		one_correct(data, a);
}

void	two_correct(t_stats *data, t_node **a) // nu 2 op goede plek, check 3e
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->n_index == (*a)->n_index - 1)
	{
		rra(a);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}

void	one_correct(t_stats *data, t_node **a) // niet 2 op goede plek, maar 3e mag wel
{
	if (data->bottom_stack->n_index == (*a)->next->n_index - 1)
	{
		rra(a);
		sa(a);
		data->lower--;
		data->bottom--;
		if ((*a)->n_index == (*a)->next->n_index - 1)
		{
			data->bottom--;
			data->lower--;
			data->bottom_stack = NULL;
		}
		else
		{
			ra(a);
			data->bottom_stack = find_bottom(*a);
		}
	}
	else
	{
		if ((*a)->n_index > data->bottom_stack->n_index)
			data->bottom_stack = *a;
		ra(a);
	}
}
