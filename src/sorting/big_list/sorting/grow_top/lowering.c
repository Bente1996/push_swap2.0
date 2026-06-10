/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   lowering.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:41:06 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:51 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>



void	try_third(t_stats *data, t_node **A)
{
	data->bottom_stack = check_bottom(*A);
	if (data->bottom_stack->n_index == (*A)->n_index - 1)
	{
		rra(A, data->top);
		rra(A, data->top);
		sa(A, data->top);
		data->lower--;
		data->bottom--;
	}
	if ((*A)->n_index != (*A)->next->n_index - 1)
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	check_third(t_stats *data, t_node **A)
{
	data->lower--;
	data->bottom--;
	if (data->bottom_stack->n_index == (*A)->n_index - 1) // maak ff 1 statement
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
	}
	data->bottom_stack = NULL;
}

bool	add_second(t_stats *data, t_node **A)
{
	if (data->bottom_stack->n_index == (*A)->n_index - 1) // tweede mag ook
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(*A);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->n_index == (*A)->n_index - 1)
		{
			rra(A, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	add_third(t_stats *data, t_node **A)
{
	rra(A, data->top);
	sa(A, data->top);
	data->lower--;
	data->bottom--;
	if ((*A)->n_index == (*A)->next->n_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
}

#include <stdio.h>

void	get_third(t_stats *data, t_node **A)
{
	printf("A EERST: %d\n", (*A)->n_index);
	printf("A->next EERST: %d\n", (*A)->next->n_index);
	printf("BOttom EERst; %d\n", data->bottom_stack->n_index);
	if ((*A)->n_index == 445)
		print_list(*A, 'A');
	rra(A, data->top);
	sa(A, data->top);
	ra(A, data->top);
	sa(A, data->top);

//	rra(A, data->top); // alle 3 nu boven
//	if (!((*A)->n_index == (*A)->next->n_index - 1))
//		sa(A, 0);
//	data->bottom_stack = NULL;
//	data->bottom -= 2;
//	data->lower -= 3;
	printf("bottom VOOR: %d\n", data->bottom);
	printf("lower VOOR: %d\n", data->lower);
//	printf("bottom: %d\n", data->bottom);
	data->bottom_stack = find_bottom(*A);
	printf("a: %d\n", (*A)->n_index);
	printf("a->next: %d\n", (*A)->next->n_index);
	printf("bottom: %d\n", data->bottom_stack->n_index);
	if ((*A)->n_index == (*A)->next->n_index - 1) // check if bottom fits too
		funk(data, A);
	else if (data->bottom_stack->n_index == (*A)->next->n_index - 1) // get
																	 // bottom
																	 // move 1
																	 // down
		fonk(data, A);
	else
	{
		if ((*A)->n_index > data->bottom_stack->n_index)
			data->bottom_stack = *A;
		ra(A, data->top);
	}
	if (data->bottom == 1)
		print_list(*A, 'A');
	printf("bottom NA: %d\n", data->bottom);
	printf("lower NA: %d\n", data->lower);
	printf("a NA: %d\n", (*A)->n_index);
	printf("a->next NA: %d\n", (*A)->next->n_index);
	if (data->bottom)
		printf("bottom NA: %d\n", data->bottom_stack->n_index);
}
