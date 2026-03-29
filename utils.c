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

bool	in_group(int sorted_index)
{
	static int	arr[5] = {0};

	if (sorted_index == highest - 1)
		arr[0] = 1;
	else if (sorted_index == highest - 2)
		arr[1] = 10;
	else if (sorted_index == higest - 3)
		arr[2] = 100;
	else if (sorted_index == highest - 4)
		arr[3] = 1000;
	else if (sorted_index == highest - 5)
		arr[4] = 10000;
	else
		return (false);
}

int	shift_group(int	*arr, int highest)
{
	int	i;
	int	sum;

	i = 0;
	while (i < 5)
		sum += arr[i];
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
	adapt_group(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(highest);
}

void	adapt_group(int *arr, int sum)
{
	int	i;

	i = 0;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
	{
		while (i + 1 < 5) // check 2, 3, 4
		{
			arr[i] == arr[i + 1]; // inhoud array 2 gaat naar array 1
			i++;
		}
	}
	else if (sum == 11)
	{
		while (i + 2 < 5) //  sla eerste twee over
		{
			arr[i] == arr[i + 2];
			i++;
		}
	}
	else if (sum == 111)
	{
		while (i + 3 < 5)
		{
			arr[i] == arr[i + 3];
			i++;
		}
	}
	else if (sum == 1111)
	{
		while (i + 4 < 5)
		{
			arr[i] == arr[i + 4];
			i++;
		}
	}
	i = 4;
	while (sum >= 1) // zet nodige arrays op 0
	{
		arr[i] = 0;
		i--;
		sum /= 10;
	}
}
