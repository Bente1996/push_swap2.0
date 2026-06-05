/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   rb.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:39:51 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:40:21 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	rb(t_node **B, int top)
{
	t_node	*first;
	t_node	*tmp;

	if (!*B || !(*B)->next)
		return ;
	if (top)
		return (ra(B, top - 1));
	first = *B;
	tmp = *B;
	*B = (*B)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;
	count_operations("rb");
}
