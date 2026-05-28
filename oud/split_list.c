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

void	mark_gaps(t_node *A, int half)
{
	t_node	*head;
	int	top;

	head = A;
	top = 0;
	while (A->next)
	{
		if (A->is_group_top)
		{
			if (A->n_index > top) // zoek hoogste top
				top = A->n_index;
		}
		else if (A->is_group_h)
		{
			if (A->n_index < half)
				half = A->n_index;
		}
		A = A->next;
	}
	while (head->next)
	{
		if (head->n_index < top)
			head->is_group_top = true;
		else if (head->n_index > half)
			head->is_group_h = true;
		head = head->next;
	}
}

void	mark_group(t_node *A, int half)
{
	static int	arr[3];
	static int	array[3];
	static int	top;
	static int	h;

	if (h == 0)
		h = half;
	if (highest_group(A, arr, h))
	{
		h = move_highest(arr, h); // verander zoekcriteria op basis van group shift
		A->is_group_h = true;
	}
	else if (lowest_group(A, array, top))
	{
		top = move_lowest(array, top);
		A->is_group_top = true;
	}
}

void	split_list(t_node **A, t_node **B, int half)
{
	t_node *head;
	int		h;
	int		group;
//	int		count;

	head = *A;
	h = half;
	group = 0;
//	count = 0;
	while (head->next)
	{
		if (head->n_index < half)
			mark_group(head, half);
		head = head->next;
	}
	mark_gaps(*A, half);
	while (h) // push to B
	{
		if ((*A)->n_index < half)
		{
			pb(A, B);
		//	if ((*B)->is_group_top || (*B)->is_group_h)
		//	{
		//		rb(B, 0);
		//		group++;
		//	}
			if ((*B)->n_index < 3 || (*B)->n_index > half - 4) // VARIATIE
			{
				rb(B, 0);
				group++;
			}
			h--;
		}
		else
			ra(A, 0);
	}
	while (group--)
	{
		rrb(B);
	//	if ((*B)->n_index < 3 || (*B)->n_index > half - 4)
	//	{
	//		pa(A, B, 0);
	//		count++;
	//	} 
	}
	//while (count--)
	//	pb(A, B);
//	print_list(*B, 'B');
}

//void	split_list(t_node **A, t_node **B, int half) // versie zonder markeren
//{
//	int	h;
//	int	count;
//
//	h = half;
//	count = 0;
////	print_list(*A, 'A');
//	while (h)
//	{
//		if ((*A)->n_index < half)
//		{
//			pb(A, B);
//			h--;
//			if (little_organise(B, half)) // check <-50 en 0->
//				count++;
//		}
//		else
//			ra(A, 0);
//	}
//	while (count--)
//		rrb(B);
////	print_list(*B, 'B');
//}
//
//#include <stdio.h>
//
//bool	little_organise(t_node **B, int half) // highest+lowest in 1 functie
//											  // niet static
//{
//	int	arr[3];
//	int	array[3];
//	int	top;
//	int	h;
//
//	top = 0;
//	h = half;
//	if (highest_group(*B, arr, h))
//	{
//		move_highest(arr, h); // verander zoekcriteria op basis van group shift
//		rb(B, 0);
//		return (true);
//	}
//	else if (lowest_group(*B, array, top))
//	{
//		move_lowest(array, top);
//		rb(B, 0);
//		return (true);
//	}
//		return (false);
//}

//bool	little_organise(t_node **B, int half) // highest+lowest in 1 functie
//											  // static
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
//		if ((*B)->next) // kan weg
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

//bool	in_group(t_node *B, int half) // nieuwe little_organise() opzetje
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
