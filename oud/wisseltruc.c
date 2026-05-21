//nodes.c, swapping.c, big_list.c, grow_list_utils.c, grow_list.c, hundred.c, lowering.c, lowering_utils.c

#include "push_swap.h"
#include <stddef.h>

#include <stdlib.h>

t_node	*new_node(int value, int index)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = value;
	new->index = index;
	new->sorted_index = 0;
	new->next = NULL;
	return (new);
}

#include <stdio.h>

t_node	*append_node(t_node **head, int value, int index)
{
	t_node	*new;
	t_node	*tmp;

	//if (is_duplicate(*head, value))
	//	return (NULL);
	new = new_node(value, index);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_stats	*alloc_stats(t_node **stack_a, t_node **stack_b, int half)
{
	t_stats	*data;
	int	all;

	all = half * 2;
	data = malloc(sizeof(t_stats));
	if (!data)
		return (NULL);
	data->stack_a = *stack_a;
	data->stack_b = *stack_b;
	if (!already_sorted(*stack_b) && !already_sorted(*stack_a)) // als stack_a niet gesorteerd
		data->top = 1;
	else
		data->top = 0; // voeg toe aan big_list en bl_two? mss
	data->quarter = half / 2;
	data->lower = --half;
	data->three_quarter = all - (half / 2) - 1;
	data->h = half + 1;
	data->tq = data->three_quarter + 1;
	data->bottom_stack = NULL;
	return (data);
}

void	swap(t_stats *data)
{
	if ((data->stack_a->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rrb(&data->stack_b);
	if (data->swap_rot == 2)
		rrb(&data->stack_b);
	pb(&data->stack_a, &data->stack_b);
	rb(&data->stack_b, 0);
	data->bottom_stack = find_bottom(data->stack_b);
	if (data->swap_rot == 2)
	{
		if (data->stack_b->sorted_index > data->stack_b->next->sorted_index)
			sb(&data->stack_b);
		while (data->swap_rot)
		{
			rb(&data->stack_b, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_b->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		rb(&data->stack_b, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		rb(&data->stack_b, 0);
	data->bottom_stack = find_bottom(data->stack_b);
	data->tq++;
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
	rb(&data->stack_b, 0);
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
	rb(&data->stack_b, 0);
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
}

void	big_list(t_node **stack_a, t_node **stack_b, int half) // werkt met + 2
{
	t_stats *data;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	while (data->stack_a) // alles naar b: 73_50 0-49(random) 74_99
	{
		if ((data->stack_a->sorted_index >= data->tq && \
				data->stack_a->sorted_index <= data->tq + 2) && \
				data->stack_a->sorted_index > data->three_quarter) // 75->99
			upper_quarter(data);
		else if ((data->stack_a->sorted_index >= data->h && \
				data->stack_a->sorted_index <= data->h + 2) && \
				data->stack_a->sorted_index <= data->three_quarter) // 50->74	
			lower_quarter(data);
		else // was niet de goeie
			ra(&data->stack_a, 0);
	}
	*stack_a = NULL;
	*stack_b = data->stack_b;
}

void	upper_quarter(t_stats *data)
{
	if (((data->stack_a->sorted_index == data->tq + 1) || (data->stack_a->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pb(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_b->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_b;
		rb(&data->stack_b, 0);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_a->sorted_index == data->tq)
		swap(data);
	else if (data->stack_a->sorted_index == data->tq)
	{
		pb(&data->stack_a, &data->stack_b);
		rb(&data->stack_b, 0);
		data->tq++;
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

void	sorted_to_A(t_node **A, t_node **B, int half, int quarter)
{
	quarter++;
	while (half > quarter)
	{
		rrb(B);
		pa(A, B, 0);
		half--;
	}
	while (half--)
		pa(A, B, 0);
}

void	grow_list(t_node **stack_a, t_node **stack_b, int half, int count) // werkt normaal
{
	t_stats	*data;
	int	n;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ; // free en exit (1)
	while (count--)
	{
		n = find_case(data->stack_b->sorted_index, data->lower, data->bottom); // goed
		if (n == 1)
			add_and_lower(data);
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
			add(data);
		else // rest
		{
			rb(&data->stack_b, data->top);
			count++;
		}
		*stack_a = data->stack_a;
		*stack_b = data->stack_b;
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

void	add_and_lower(t_stats *data)
{
	if (data->stack_b->sorted_index == data->lower - 1)
	{
		pa(&data->stack_a, &data->stack_b, data->top);
		data->swap++;
		data->lower++;
	}
	else if (data->swap) // lower met swap
	{
		pa(&data->stack_a, &data->stack_b, data->top);
		sa(&data->stack_a, data->top);
		data->swap = 0;
		if (data->bottom)
			handle_bottom(data);
		data->lower--; // toegevoegd
	}
	else // lower geen swap
	{
		pa(&data->stack_a, &data->stack_b, data->top);
		if (data->bottom)
			handle_bottom(data); // zelfde als boven miscchien?
	}
	data->lower--;
}

void	add(t_stats *data)
{
	if (!data->bottom || data->bottom_stack->sorted_index < data->stack_b->sorted_index)
	{
		pa(&data->stack_a, &data->stack_b, data->top);
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
	else
	{
		pa(&data->stack_a, &data->stack_b, data->top);
		ra(&data->stack_a, data->top);
	}
	data->bottom++;
}

void	big_list_two(t_node **stack_a, t_node **stack_b, int half) // alles omgedraaid beetje silly, verander namen (three_quarter -> quarter, A vs B)
{
	t_stats *data;

	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	data->three_quarter = data->quarter;
	data->h = half - 1;
	data->tq = 0;
	while (data->stack_b)
	{
		if ((data->stack_b->sorted_index >= data->tq && \
				data->stack_b->sorted_index <= data->tq + 2) && \
				data->stack_b->sorted_index < data->three_quarter) // 0-24
			upper_quarter_two(data);
		else if ((data->stack_b->sorted_index <= data->h && \
				data->stack_b->sorted_index >= data->h - 2) && \
				data->stack_b->sorted_index >= data->three_quarter) // 25-49
			lower_quarter_two(data);
		else // was niet de goeie
			rb(&data->stack_b, 0);
	}
	while (data->quarter--)
		rra(&data->stack_a, 0);
	*stack_b = NULL;
	*stack_a = data->stack_a;
}

void	upper_quarter_two(t_stats *data)
{
	if (((data->stack_b->sorted_index == data->tq + 1) || (data->stack_b->sorted_index == data->tq + 2)) && data->swap_rot < 2)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_a->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a, 0);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_b->sorted_index == data->tq)
		swap_t(data);
	else if (data->stack_b->sorted_index == data->tq)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		ra(&data->stack_a, 0);
		data->tq++;
	}
}

void	lower_quarter_two(t_stats *data)
{
	if ((data->stack_b->sorted_index == data->h - 1 || data->stack_b->sorted_index == data->h - 2) && data->swap < 2)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		data->swap++;
	}
	else if (data->swap && data->stack_b->sorted_index == data->h)
		swop_t(data);
	else if (data->stack_b->sorted_index == data->h)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		data->h--;
	}
}

void	swap_t(t_stats *data)
{
	if ((data->stack_b->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rra(&data->stack_a, 0);
	if (data->swap_rot == 2)
		rra(&data->stack_a, 0);
	pa(&data->stack_a, &data->stack_b, 0);
	ra(&data->stack_a, 0);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->swap_rot == 2)
	{
		if (data->stack_a->sorted_index > data->stack_a->next->sorted_index)
			sa(&data->stack_a, 0);
		while (data->swap_rot)
		{
			ra(&data->stack_a, 0);
			data->swap_rot--;
			data->tq++;
		}
	}
	else if (data->stack_a->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		ra(&data->stack_a, 0);
		data->tq++;
		data->swap_rot--;
	}
	else
		ra(&data->stack_a, 0);
	data->bottom_stack = find_bottom(data->stack_a);
	data->tq++;
}



void	swop_t(t_stats *data)
{
	if (data->swap == 1)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		sa(&data->stack_a, 0);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		swap_two_t(data);
	data->h--;
}

void	swap_two_t(t_stats *data)
{
	ra(&data->stack_a, 0);
	if (data->stack_a->sorted_index == data->stack_b->sorted_index - 1)
	{
		pa(&data->stack_a, &data->stack_b, 0);
		sa(&data->stack_a, 0);
		data->swap--;
		data->h--;
		rra(&data->stack_a, 0);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
	else
		more_swap_t(data);
}

void	more_swap_t(t_stats *data)
{
	ra(&data->stack_a, 0);
	pa(&data->stack_a, &data->stack_b, 0);
	rra(&data->stack_a, 0);
	rra(&data->stack_a, 0);
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1)
	{
		sa(&data->stack_a, 0);
		data->swap--;
		data->h--;
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			data->swap--;
			data->h--;
		}
	}
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

int	move_quarter(int *arr, int quarter)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 5 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		quarter++;
	else if (sum == 11)
		quarter += 2;
	else if (sum == 111)
		quarter += 3;
//	else if (sum == 1111)
//		highest -= 4;
//	else if (sum == 11111)
//		highest -= 5;
	else
		return (quarter);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(quarter);
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

bool	in_group(t_node *stack_b, int *arr, int highest)
{
	if (stack_b->sorted_index == highest - 1)
		arr[0] = 1;
	else if (stack_b->sorted_index == highest - 2)
		arr[1] = 10;
	else if (stack_b->sorted_index == highest - 3)
		arr[2] = 100;
//	else if (stack_b->sorted_index == highest - 4)
//		arr[3] = 1000;
//	else if (stack_b->sorted_index == highest - 5)
//		arr[4] = 10000;
	//else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
	//	return (true);
	else
		return (false);
	return (true);
}

bool	in_other_group(t_node *stack_b, int *arr, int quarter)
{
	if (stack_b->sorted_index == quarter)
		arr[0] = 1;
	else if (stack_b->sorted_index == quarter + 1)
		arr[1] = 10;
	else if (stack_b->sorted_index == quarter + 2)
		arr[2] = 100;
//	else if (stack_b->sorted_index == highest - 4)
//		arr[3] = 1000;
//	else if (stack_b->sorted_index == highest - 5)
//		arr[4] = 10000;
	//else if (stack_b->sorted_index < highest - 5 && stack_b->sorted_index > highest - 15) // toegevoegd
	//	return (true);
	else
		return (false);
	return (true);
}

int	random_split(t_node **stack_a, t_node **stack_b, int all) // test: group op A
															   // ipv B
{
	int	arr[5] = {0};
	static	int	array[3];
	int		half;
	int		highest;
	int		h;
      	int		operations;
	int		count;
	int		quarter;

      	half = all / 2;
	h = half;
	highest = half;
	quarter = 0;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half)
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a, 0);
		if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
		{
			highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
			if ((*stack_b)->next)
				rb(stack_b, 0);
			count++;
		}
		else if (*stack_b && in_other_group(*stack_b, array, quarter))
		{
			quarter = move_quarter(array, quarter);
			if ((*stack_b)->next)
				rb(stack_b, 0);
			count++;
		}
	}
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	big_list(stack_a, stack_b, half);
	if (all % 2)
		sorted_to_A(stack_a, stack_b, half + 1, half / 2);
	else
		sorted_to_A(stack_a, stack_b, half, half / 2);
	big_list_two(stack_a, stack_b, half); // 672 group 5
	operations = 1;
	return (operations);
}

void	handle_bottom(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // wanneer er iig 1 naar boven moet
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			more_bottom(data);
		else
			data->bottom_stack = NULL;
	}
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

void	try_three(t_stats *data)
{
	data->bottom_stack = check_bottom(data->stack_a);
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(&data->stack_a, data->top);
		rra(&data->stack_a, data->top);
		sa(&data->stack_a, data->top);
		data->lower--;
		data->bottom--;
	}
	if (data->stack_a->sorted_index != data->stack_a->next->sorted_index - 1)
	{
		ra(&data->stack_a, data->top);
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
	rra(&data->stack_a, data->top);
	if (data->bottom == 2)
		data->bottom_stack = find_bottom(data->stack_a);
	else
		data->bottom_stack = data->stack_a->next;
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1) // als tweede goed is
	{
		sa(&data->stack_a, data->top);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1) // twee op juiste plek
			check_third(data);
		else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1) // niet twee juiste volgorde
			get_second(data);
		else // tweede was niet goed
		     ra(&data->stack_a, data->top);
	}
	else // tweede was niet goed, dus moet derde wel zijn
		 get_third(data);
}

bool	add_second(t_stats *data)
{
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // tweede mag ook
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(data->stack_a);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
		{
			rra(&data->stack_a, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	check_third(t_stats *data)
{
	data->lower--;
	data->bottom--;
	if (data->bottom && data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1) // maak ff 1 statement
	{
		rra(&data->stack_a, data->top);
		data->bottom_stack = NULL;
		data->bottom--;
		data->lower--;
	}
	else
		data->bottom_stack = NULL;
}

void	funk(t_stats *data)
{
	data->bottom--;
	data->lower--;
	if (data->bottom_stack->sorted_index == data->stack_a->sorted_index - 1)
	{
		rra(&data->stack_a, data->top);
		data->bottom--;
		data->lower--;
		data->bottom_stack = NULL;
	}
}

void	get_third(t_stats *data)
{
	rra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
	ra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		funk(data);
	else if (data->bottom_stack->sorted_index == data->stack_a->next->sorted_index - 1)
		fonk(data);
	else
	{
		if (data->stack_a->sorted_index > data->bottom_stack->sorted_index)
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a, data->top);
	}
}

void	get_second(t_stats *data)
{
	rra(&data->stack_a, data->top);
	data->lower--;
	data->bottom--;
	sa(&data->stack_a, data->top);
	if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}

void	fonk(t_stats *data)
{
	rra(&data->stack_a, data->top);
	sa(&data->stack_a, data->top);
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
		ra(&data->stack_a, data->top);
		data->bottom_stack = find_bottom(data->stack_a);
	}
}
