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
		//printf("Sorted index:%d\n", list->sorted_index);
		list = list->next;
	}
}

int	count_operations(char *operation)
{
	static int	operation_count;

	operation_count++;
	printf("%s\n", operation); // vervang door ft_printf
	return (operation_count);
}

bool	sorted(t_node *stack, int half, char stack)
{
	while (stack)
	{
		if (stack == 'A' && stack->sorted_index <= half)
			stack = stack->next;
		else if (stack == 'B' && stack->sorted_index > half)
			stack = stack->next;
		else
			return (false);
	}
	return (true);
}
