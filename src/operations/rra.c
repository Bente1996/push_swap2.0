/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   rra.c                                                   :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:40:34 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:41:03 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	rra(t_node **A, int top)
{
	t_node	*second_last;
	t_node	*last;

	if (!*A || !(*A)->next)
		return ;
	if (top)
		return (rrb(A));
	second_last = *A;
	last = *A;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *A;
	*A = last;
	count_operations("rra");
}
