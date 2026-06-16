/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sa.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:36:50 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:37:48 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	sa(t_node **A)
{
	t_node	*first;
	t_node	*second;

	if (!*A || !(*A)->next)
		return ;
	first = *A;
	second = (*A)->next;
	first->next = (*A)->next->next;
	second->next = *A;
	*A = second;
	count_operations("sa");
}
