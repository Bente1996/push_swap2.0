/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   sort_big_list.c                                         :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:40:38 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:40:40 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_big_list(t_node **a, t_node **b, int all, int size)
{
	int	sorted;
	int	half;

	half = all / 2;
	sorted = half - size;
	organise_b(a, b, half, size);
	organise_a(a, b, all, half + size);
	if (all % 2)                              // all to B, (half - size sorted)
	{
		sort_unorganised(b, a, all, half - size + 1);
		sorted++;
	}
	else
		sort_unorganised(b, a, all, half - size);
	while (sorted--)                          // 500->430 sorted in A
	{
		pa(a, b, 0);
		ra(a, 0);
	}
	half_stack_sorted(a, b, half + size, size);       // 250->500 sorted in A
	half_stack_sorted(a, b, half, half);              // all sorted in A (2x sort half
											  // stack)
	//print_list(*a, 'A');
	//print_list(*b, 'B');
}

//void	sort_big_list(t_node **a, t_node **b, int all, int size)
//{
//	int	sorted;
//	int	half;
//
//	half = all / 2;
//	sorted = half - size;
//	organise_b(a, b, half, size);
//	organise_a(a, b, all, half + size);
//	if (all % 2)                              // all to B, (half - size sorted)
//	{
//		grow_list(b, a, all, half - size + 1);
//		sorted++;
//	}
//	else
//		grow_list(b, a, all, half - size);
//	while (sorted--)                          // 500->430 sorted in A
//	{
//		pa(a, b, 0);
//		ra(a, 0);
//	}
//	grow_list(a, b, half + size, size);       // 250->500 sorted in A
//	grow_list(a, b, half, half);              // all sorted in A (2x sort half
//											  // stack)
//	//print_list(*a, 'A');
//	//print_list(*b, 'B');
//}
