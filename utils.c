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
	if (!list)
		return ;
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
	if (!stack)
		return (false);
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

int	find_case(int sorted_index, int lower, int bottom)
{
	if (sorted_index == lower || sorted_index == lower - 1)
		return (1);
	else if ((sorted_index == lower - 2 || sorted_index == lower - 3 || sorted_index == lower - 4) && bottom < 3)
		return (2);
	else
		return (0);
}

void	case_one(t_stats *data)
{
	if (data->stack_b->sorted_index == data->lower - 1)
	{
		pa(&data->stack_a, &data->stack_b);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data);
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(&data->stack_a, &data->stack_b);
		if (data->bottom)
			handle_bottom(data); // zelfde als boven miscchien?
	}
	data->lower--;
}

void	handle_bottom(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // wanneer er iig 1 naar boven moet
	{
		rra(&data->stack_a);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			more_bottom(data);
		else
			data->bottom_stack = NULL;
	}
}

bool	add_second(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // tweede mag ook
	{
		rra(&data->stack_a);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(data->stack_a);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
		{
			rra(&data->stack_a);
			data->lower--;
			data->bottom_stack = NULL;
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
		rra(&data->stack_a);
		rra(&data->stack_a);
		sa(&data->stack_a);
		data->lower--;
		data->bottom--;
	}
	if (data->stack_a->sorted_index != data->stack_a->next->sorted_index - 1)
	{
		ra(&data->stack_a);
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
	rra(&data->stack_a);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(data->stack_a);
	else
		data->bottom_stack = data->stack_a->next;
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1) // als tweede goed is
	{
		sa(&data->stack_a);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // twee op juiste plek
			check_third(data);
		else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1) // niet twee juiste volgorde
			get_second(data);
		else // tweede was niet goed
		     ra(&data->stack_a);
	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third(data);
}

void	more_bottom(t_stats *data)
{
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // eerste was goed
	{
		data->bottom_stack = find_bottom(data->stack_a);
		if (!add_second(data) && data->bottom == 2) // check tweede
				try_three(data); // tweede mag niet, probeer derde
	}
	else // eerste was niet goed dus probeer tweede
		 try_two(data);
}

void	check_third(t_stats *data)
{
	data->lower--;
	data->bottom--;
	if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // maak ff 1 statement
	{
		rra(&data->stack_a);
		data->bottom_stack = NULL;
		data->bottom--;
		data->lower--;
	}
	else
		data->bottom_stack = NULL;
}

void	get_second(t_stats *data)
{
	rra(&data->stack_a);
	data->lower--;
	data->bottom--;
	sa(&data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(&data->stack_a);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}

void	get_third(t_stats *data)
{
	rra(&data->stack_a);
	sa(&data->stack_a);
	ra(&data->stack_a);
	sa(&data->stack_a);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		funk(data);
	else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1)
		fonk(data);
	else
	{
		if (data->stack_a->sorted_index > data->bottom_stack->sorted_index)
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a);
	}
}

void	funk(t_stats *data)
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(&data->stack_a);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}

void	fonk(t_stats *data)
{
	rra(&data->stack_a);
	sa(&data->stack_a);
	data->lower--;
	data->bottom--;
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
	{
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(&data->stack_a);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}

void	case_two(t_stats *data)
{
	if (!data->bottom || data->bottom_stack->sorted_index < data->stack_b->sorted_index)
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
		data->bottom_stack = find_bottom(data->stack_a);
	}
	else
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
	}
	data->bottom++;
}

void	swap(t_stats *data)
{
	if ((data->stack_a->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rrb(&data->stack_b);
	if (data->swap_rot == 2)
		rrb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rb(&data->stack_b);
	data->bottom_stack = find_bottom(data->stack_b);
	if (data->swap_rot == 2)
	{
		if (data->stack_b->sorted_index > data->stack_b->next->sorted_index)
			sb(&data->stack_b);
		while (data->swap_rot)
		{
			rb(&data->stack_b);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_b->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		rb(&data->stack_b);
		data->tq++;
		data->swap_rot--;
	}
	else
		rb(&data->stack_b);
	data->bottom_stack = find_bottom(data->stack_b);
	data->tq++;
}

void	upper_quarter(t_stats *data)
{
	if (((data->stack_a->sorted_index == data->tq + 1) || (data->stack_a->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_b->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_b;
		rb(&data->stack_b);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_a->sorted_index == data->tq)
		swap(data);
	else if (data->stack_a->sorted_index == data->tq)
	{
		pb(&data->stack_a, &data->stack_b);
		rb(&data->stack_b);
		data->tq++;
	}
}

void	swop(t_stats *data)
{
	if (data->swap == 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		swap_two(data);
	data->h++;
}

void	swap_two(t_stats *data)
{
	rb(&data->stack_b);
	if (data->stack_b->sorted_index == data->stack_a->sorted_index + 1)
	{
		pb(&data->stack_a, &data->stack_b);
		sb(&data->stack_b);
		data->swap--;
		data->h++;
		rrb(&data->stack_b);
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else
		more_swap(data);
}

void	more_swap(t_stats *data)
{
	rb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rrb(&data->stack_b);
	rrb(&data->stack_b);
	if (data->stack_b->sorted_index == data->stack_b->next->next->sorted_index + 1)
	{
		sb(&data->stack_b);
		data->swap--;
		data->h++;
		if (data->stack_b->sorted_index == data->stack_b->next->sorted_index + 1)
		{
			data->swap--;
			data->h++;
		}
	}
	else // toegevoegd vanwege mysterie
	{
		data->swap -= 2;
		data->h += 2;
	}
}

void	lower_quarter(t_stats *data)
{
	if ((data->stack_a->sorted_index == data->h + 1 || data->stack_a->sorted_index == data->h + 2) && data->swap < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		data->swap++;
	}
	else if (data->swap && data->stack_a->sorted_index == data->h)
		swop(data);
	else if (data->stack_a->sorted_index == data->h)
	{
		pb(&data->stack_a, &data->stack_b);
		data->h++;
	}
}
