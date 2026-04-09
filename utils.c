/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   utils.c                                                 :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:15:19 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:15:23 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

bool	is_number(char *argv)
{
	if (*argv == '-')
		argv++;
	while (*argv)
	{
		if (*argv++ < '0' || *argv > '9')
			return (false);
	}
	return (true);
}

bool	is_overflow(char *argv, int value, int sign)
{
	if (value < 214748364)
		return (false);
	else if (value == 214748364)
	{
		if (*argv > '8')
			return (true);
		if (*argv == '8' && sign == 1)
			return (true);
		return (false);
	}	
	else
		return (true);
}

bool	is_duplicate(t_node *head, int value)
{
	while (head)
	{
		if (head->value == value)
			return (true);
		head = head->next;
	}
	return (false);
}

void	free_list(t_node *head)
{
	t_node	*tmp;


	while (head)
	{
		tmp = head;
		head = head->next;
		free (tmp);
	}
}

#include <stdio.h>

void	print_list(t_node *list, char stack)
{
	if (stack == 'A')
		printf("\nStack A:\n");
	if (stack == 'B')
		printf("\nStack B:\n");
	while (list)
	{
		printf("Value:%d\n", list->value);
		//printf("Index:%d\n", list->index);
		printf("Sorted index:%d\n", list->sorted_index);
		list = list->next;
	}
}

int	count_operations(char *operation)
{
	static int	operation_count;

	operation_count++;
	//printf("%s\n", operation); // vervang door ft_printf
	operation++; // alleen zodat printen niet hoeft
	return (operation_count);
}

bool	sorted(t_node *stack, int half, char A_or_B) // veranderd
{
	while (stack)
	{
		if (A_or_B == 'A' && stack->sorted_index >= half)
			stack = stack->next;
		else if (A_or_B == 'B' && stack->sorted_index <= half)
			stack = stack->next;
		else
			return (false);
	}
	return (true);
}

bool	one_element(t_node **stack_a, t_node **stack_b, int half) // stop in sorted()
{
	if (stack_size(*stack_a) != 1 && stack_size(*stack_b) != 1)
		return (false);
	if (stack_size(*stack_a) == 1 && (*stack_a)->sorted_index <= half)
		pb(stack_a, stack_b);
	else if (stack_size(*stack_b) == 1 && (*stack_b)->sorted_index > half)
		pa(stack_a, stack_b);
	return (true);
}

int	stack_size(t_node *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}

bool	already_sorted(t_node *stack)
{
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

t_node	*check_bottom(t_node *stack)
{
	while (stack->next->next)
		stack = stack->next; // naar een na laatste
	return (stack);
}

t_node	*find_bottom(t_node *stack)
{
	while (stack->next)
		stack = stack->next;
	return (stack);
}

bool	in_group(t_node *stack_b, int *arr, int highest)
{
	if (stack_b->sorted_index == highest - 1)
		arr[0] = 1;
	else if (stack_b->sorted_index == highest - 2)
		arr[1] = 10;
	else if (stack_b->sorted_index == highest - 3)
		arr[2] = 100;
	else if (stack_b->sorted_index == highest - 4)
		arr[3] = 1000;
	else if (stack_b->sorted_index == highest - 5)
		arr[4] = 10000;
	else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
		return (true);
	else
		return (false);
	return (true);
}

int	move_highest(int *arr, int highest)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 5 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		highest--;
	else if (sum == 11)
		highest -= 2;
	else if (sum == 111)
		highest -= 3;
	else if (sum == 1111)
		highest -= 4;
	else if (sum == 11111)
		highest -= 5;
	else
		return (highest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(highest);
}

void	shift_group(int *arr, int n)
{
	int	shrink;
	int	i;

	i = 0;
	shrink = 1;
	while (i + n < 5)
	{
		if (arr[i + n])
			arr[i] = arr[i + n] - (shrink * 9);
		else
			arr[i] = 0;
		i++;
		shrink *= 10;
	}
}

void	check_shift(int *arr, int sum)
{
	int	i;

	i = 4;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
		shift_group(arr, 1);
	else if (sum == 11)
		shift_group(arr, 2); 
	else if (sum == 111)
		shift_group(arr, 3);
	else if (sum == 1111)
		shift_group(arr, 4);
	while (sum >= 1) // zet nodige arrays op 0
	{
		arr[i--] = 0;
		sum /= 10;
	}
}


void	sorted_to_A(t_node **A, t_node **B, int half, int quarter)
{
	while (half > quarter)
	{
		rrb(B);
		pa(A, B);
		half--;
	}
	while (half)
	{
		pa(A, B);
		half--;
	}
}

int	find_case(int sorted_index, int lower)
{
	if (sorted_index == lower || sorted_index == lower - 1)
		return (1);
	else if (sorted_index == lower - 2 || sorted_index == lower - 3 || sorted_index == lower - 4)
		return (2);
	else
		return (0);
}

void	case_one(t_stats *data)
{
	if (data->stack_b->sorted_index == data->lower - 1)
	{
		pa(data->head_a, data->head_b);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(data->head_a, data->head_b);
		sa(data->head_a);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data);
	}
	else // lower geen swap
	{
		pa(data->head_a, data->head_b);
		if (data->bottom)
			handle_bottom(); // zelfde als boven miscchien?
	}
	data->lower--;
}

void	handle_bottom(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // wanneer er iig 1 naar boven moet
	{
		rra(data->head_a);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			more_bottom();
		else
			data->bottom_stack = NULL;
	}
}

bool	add_second(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // tweede mag ook
	{
		rra(data->head_a);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(data->stack_a);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
		{
			rra(data->head_a);
			rra(data->head_a);
			data->lower--;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	try_three(t_stats *data)
{
	data->bottom_stack = check_bottom(data->stack_a);
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(data->head_a);
		rra(data->head_a);
		sa(data->head_a);
		data->lower--;
		data->bottom--;
	}
	if (data->stack_a->sorted_index != data->stack_a->next->sorted_index - 1)
	{
		ra(data->head_a);
		data->bottom_stack = find_bottom(data->stack_a);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	try_two(t_stats *data)
{
	rra(data->head_a;
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(data->stack_a);
	else
		data->bottom_stack = data->stack_a->next;
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1) // als tweede goed is
	{
		sa(data->head_a);
		if (data->stack_a->sorted_index == data->stack_a->sorted_index - 1) // twee op juiste plek
			check_third();
		else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1) // niet twee juiste volgorde

		else // tweede was niet goed

	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third();
}

void	more_bottom(t_stats *data)
{
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(data->stack_a);
		if (!add_second(data)) // check tweede
		{
			if (data->bottom == 2) // tweede mag niet, probeer derde
				try_three(data);
		}
	}
	else // eerste was niet goed dus probeer tweede
		 try_two(data);
}

void	case_two(t_stats *data)
{
	if (data->bottom < 3)
	{
		if (!data->bottom || data->bottom_stack->sorted_index < data->stack_b->sorted_index)
		{
			pa(data->head_a, data->head_b);
			ra(data->head_a);
			data->bottom_stack = find_bottom(data->stack_a);
		}
		else
		{
			pa(data->head_a, data->head_b);
			ra(data->head_a);
		}
		data->bottom++;
	}
}








