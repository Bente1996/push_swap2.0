/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   ra.c                                                    :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/05 21:39:09 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/05 21:39:43 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

void	ra(t_node **A)
{
	t_node	*first;
	t_node	*tmp;

	if (!*A || !(*A)->next)
		return ;
	first = *A;
	tmp = *A;
	*A = (*A)->next; //nieuwe hoofd
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;// bij uiteinde 
	count_operations("ra");
}
