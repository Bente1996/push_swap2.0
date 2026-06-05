/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   pa.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:33:55 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:35:57 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	pa(t_node **A, t_node **B, int top)
{
	t_node	*tmp;

	if (!*B)
		return ;
	if (top)
		return (pb(B, A));
	tmp = *B;
	*B = (*B)->next;
	tmp->next = NULL;
	if (!*A)
		*A = tmp;
	else
	{
		tmp->next = *A;
		*A = tmp;
	}
	count_operations("pa");
}
