/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   split_list.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/25 16:52:58 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/25 17:02:56 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	split_list(t_node **A, t_node **B, int half)
{
	int	h;
	int	count;

	h = half;
	count = 0;
	while (h)
	{
		if ((*A)->n_index < half)
		{
			pb(A, B);
			h--;
			if (little_organise(B, half)) // check <-50 en 0->
				count++;
		}
		else
			ra(A, 0);
	}
	while (count--)
		rrb(B);
//	print_list(*B, 'B');
//	print_list(*A, 'A');
}

#include <stdio.h>

bool	little_organise(t_node **B, int half) // highest+lowest in 1 functie
											  // doen
{
	int	arr[3];
	int	array[3];
	int	top;
	int	h;

	top = 0;
	h = half;
	if (highest_group(*B, arr, h))
	{
		move_highest(arr, h); // verander zoekcriteria op basis van group shift
		rb(B, 0);
		return (true);
	}
	else if (lowest_group(*B, array, top))
	{
		move_lowest(array, top);
		rb(B, 0);
		return (true);
	}
		return (false);
}

//bool	little_organise(t_node **B, int half) // highest+lowest in 1 functie
//											  // doen
//{
//	static int	arr[3];
//	static int	array[3];
//	static int	top;
//	static int	h;
//
//	if (h == 0)
//		h = half;
//	if (highest_group(*B, arr, h))
//	{
//		h = move_highest(arr, h); // verander zoekcriteria op basis van group shift
//		if ((*B)->next) // WAAROM??!?!??!??!!?
//			rb(B, 0);
//		return (true);
//	}
//	else if (lowest_group(*B, array, top))
//	{
//		top = move_lowest(array, top);
//		if ((*B)->next)
//			rb(B, 0);
//		return (true);
//	}
//		return (false);
//}

//bool	in_group(t_node *B, int half)
//{
//	int	top[4];
//	int	h[4];
//
//	if (B->n_index == half - 1)
//		h[0] = 1;
//	else if (B->n_index == half - 2)
//		h[1] = 10;
//	else if (B->n_index == half - 3)
//		h[2] = 100;
//	else if (B->n_index == lowest)
//		top[0] = 1;
//	else if (B->n_index == lowest + 1)
//		top[1] = 10;
//	else if (B->n_index == lowest + 2)
//		top[2] = 100;
//
//	return (true);
//}

bool	highest_group(t_node *B, int *arr, int highest) // define
{
	if (B->n_index == highest - 1)
		arr[0] = 1;
	else if (B->n_index == highest - 2)
		arr[1] = 10;
	else if (B->n_index == highest - 3)
		arr[2] = 100;
	else
		return (false);
	return (true);
}

bool	lowest_group(t_node *B, int *arr, int lowest)
{
	if (B->n_index == lowest)
		arr[0] = 1;
	else if (B->n_index == lowest + 1)
		arr[1] = 10;
	else if (B->n_index == lowest + 2)
		arr[2] = 100;
	else
		return (false);
	return (true);
}
