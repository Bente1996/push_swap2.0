/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   rrb.c                                                   :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:41:10 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:41:42 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	rrb(t_node **B)
{
	t_node	*second_last;
	t_node	*last;

	if (!*B || !(*B)->next)
		return ;
	second_last = *B;
	last = *B;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *B;
	*B = last;
	count_operations("rrb");
}
