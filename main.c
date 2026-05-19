/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   main.c                                                  :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:17 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:16:20 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*A;
	t_node	*B;
	int		index;
//	int	operations;

	A = NULL;
	B = NULL;
	index = 0;
	if (argc < 3)
		return (1);
	A = make_list(argc, argv, &index);
	if (!A)
		return (free_list(A));
	if (already_sorted(A))
		return (free_list(A));
	sort_all(&A, &B, index);

//	operations = count_operations("");
//	print_list(stack_a, 'A');
//	print_list(stack_b, 'B');
//	printf("Operations:%d\n", operations - 1);
//	if (already_sorted(stack_a))
//		printf("GOED GESORTEERD :)");
//	else
//		printf("niet goed gesorteerd\n");
//
//	printf("stacksize: %d\n", stack_size(stack_a));
	free_list(A);
	return (0);
}
