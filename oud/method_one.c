// old: 6904

// b noramlly sorted by 5 but big_list instead of final_list: 9394
// without sorting: 8453
// sorted B by 6:

#include "push_swap.h"
#include <stdio.h>
#include <stddef.h>

void	swap_B(t_stats *data)
{
	if ((data->stack_b->sorted_index != data->bottom_stack->sorted_index + 1) || data->swap_rot == 2)
		rra(&data->stack_a);
	if (data->swap_rot == 2)
		rra(&data->stack_a);
	pa(&data->stack_a, &data->stack_b);
	ra(&data->stack_a);
	data->bottom_stack = find_bottom(data->stack_a);
	if (data->swap_rot == 2)
	{
		if (data->stack_a->sorted_index > data->stack_a->next->sorted_index)
			sa(&data->stack_a);
		while (data->swap_rot)
		{
			ra(&data->stack_a);
			data->swap_rot--;
			data->h++;
		}
	}
	else if (data->stack_a->sorted_index == data->bottom_stack->sorted_index + 1)
	{
		ra(&data->stack_a);
		data->h++;
		data->swap_rot--;
	}
	else
		ra(&data->stack_a);
	data->bottom_stack = find_bottom(data->stack_a);
	data->h++;
}


void	upper_quarter_B(t_stats *data)
{
	printf("UQ B\n");
	if (((data->stack_b->sorted_index == data->h + 1) || (data->stack_b->sorted_index == data->h + 2)) && data->swap_rot < 2)
	{
		pa(&data->stack_a, &data->stack_b);
		if (!data->swap_rot || (data->swap_rot == 1 && (data->stack_a->sorted_index > data->bottom_stack->sorted_index)))
			data->bottom_stack = data->stack_a;
		ra(&data->stack_a);
		data->swap_rot++;
	}
	else if (data->swap_rot && data->stack_b->sorted_index == data->h)
		swap_B(data);
	else if (data->stack_b->sorted_index == data->h)
	{
		pa(&data->stack_a, &data->stack_b);
		ra(&data->stack_a);
		data->h++;
	}
}

void	more_swap_B(t_stats *data)
{
	printf("halloo\n");
	ra(&data->stack_a);
	pa(&data->stack_a, &data->stack_b);
	rra(&data->stack_a);
	rra(&data->stack_a);
	printf("A%d\n", data->stack_a->sorted_index);
	printf("A%d\n", data->stack_a->next->sorted_index);
	printf("A%d\n", data->stack_a->next->next->sorted_index);
	printf("B%d\n", data->stack_b->sorted_index);
	if (data->stack_a->sorted_index == data->stack_a->next->next->sorted_index - 1)
	{
		sa(&data->stack_a);
		printf("swap%d\n", data->swap);
		data->swap--;
		printf("swap%d\n", data->swap);
		data->tq--;
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			printf("swap%d\n", data->swap);
			data->swap--;
			printf("swap%d\n", data->swap);
			data->tq--;
		}
	}
	else // toegevoegd    HEEEEEEEEEL RAAAAAAAR (zit niet in big_list wtfwtfwtfwtfwtf) // hoort hier nooit in te gaan, vandaar , maar waarom?!
	{
		printf("swap in final_list: %d\n", data->swap);
		data->swap -= 2;
		data->tq -= 2;
	}
}

void	swap_two_B(t_stats *data)
{
	printf("hallootjes\n");
	ra(&data->stack_a);
	if (data->stack_a->sorted_index == data->stack_a->sorted_index - 1)
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		data->swap--;
		data->tq--;
		rra(&data->stack_a);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			data->swap--;
			data->tq--;
		}
	}
	else
		more_swap_B(data);
}

void	swop_B(t_stats *data)
{
	printf("halloononon\n");
	printf("swop b swap: %d\n", data->swap);
	if (data->swap == 1)
	{
		pa(&data->stack_a, &data->stack_b);
		sa(&data->stack_a);
		if (data->stack_a->sorted_index == data->stack_a->next->sorted_index - 1)
		{
			data->swap--;
			data->tq--;
		}
	}
	else
		swap_two_B(data);
	data->tq--;
	printf("swop b swap: %d\n", data->swap);
}



void	lower_quarter_B(t_stats *data)
{
	printf("LQ B\n");
	printf("b->sorted_index %d\n", data->stack_b->sorted_index);
	printf("a->sorted_index %d\n", data->stack_a->sorted_index);
	printf("h %d\n", data->h);
	printf("tq %d\n", data->tq);
	printf("swap %d\n", data->swap);
	if ((data->stack_b->sorted_index == data->tq - 1 || data->stack_b->sorted_index == data->tq - 2) && data->swap < 2)
	{
		printf("1 test\n");
		pa(&data->stack_a, &data->stack_b);
		data->swap++;
	}
	else if (data->swap && data->stack_b->sorted_index == data->tq)
	{
		swop_B(data);
		printf("2 test\n");
	}
	else if (data->stack_b->sorted_index == data->tq)
	{
		pa(&data->stack_a, &data->stack_b);
		data->tq--;
		printf("3 test\n");
	}
//	printf("b->sorted_index %d\n", data->stack_b->sorted_index);
	printf("a->sorted_index %d\n", data->stack_a->sorted_index);
	printf("h %d\n", data->h);
	printf("tq %d\n", data->tq);
	printf("swap %d\n\n", data->swap);
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 2x big_list , gaat iets mis bij tq (126)
{
	t_stats *data;

	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
	data = alloc_stats(stack_a, stack_b, half - 250);
	if (!data)
		return ;
	data->h = 0;
	data->tq = 250; // andersom pushen
	data->three_quarter = 125;
	printf("final list %d %d\n", data->h, data->tq);
	int bente = 62305;
	while (data->stack_b && bente) // alles naar b: 73_50 0-49(random) 74_99
	{
		if (data->stack_b->sorted_index == 125)
			printf("bente %d\n", bente);
		if ((data->stack_b->sorted_index >= data->h && data->stack_b->sorted_index <= data->h + 2) &&	data->stack_b->sorted_index <= data->three_quarter)
		{
			upper_quarter_B(data); // eigenlijk lower
		}
		else if ((data->stack_b->sorted_index <= data->tq && data->stack_b->sorted_index >= data->tq - 2) && data->stack_b->sorted_index > data->three_quarter)	
		{
			if (data->stack_a->sorted_index == 234)
			{
				printf("is 240\n");
				printf("swap: %d\n", data->swap);
				printf("swap_rot: %d\n", data->swap_rot);
				printf("h: %d\n", data->h);
				printf("tq: %d\n", data->tq);
				break ;
			}
			lower_quarter_B(data); // eigenlijk upper
		}
		else // was niet de goeie
			rb(&data->stack_b);
		bente--;
	}
	int count = 126;
	while (count)
	{
		rra(&data->stack_a);
		count--;
	}
	if (*stack_b)
		*stack_b = data->stack_b;
	else
		*stack_b = NULL;
	*stack_a = data->stack_a;
	//print_list(data->stack_a, 'A');
	//print_list(data->stack_b, 'B');
}

// for shifting 3/3

void	organise(t_node **stack_a, t_node **stack_b)
{
	int	high[3];
	int	low[3];
	int	h;
	int	l;

	h = 0;
	l = 0;
	while (*stack_b)
	{
		if (in_group(*stack_b, high, h)) // shift upper
		{
			h = move_highest(high, h);
			pa(stack_a, stack_b);
		}
		else if (in_group(*stack_b, low, l))
		{
			l = move_highest(low, l);
			pa(stack_a, stack_b);
			ra(stack_a);
		}
	}
}

//void	split_list(t_node **stack_a, t_node **stack_b, int half)
//{
////	int	highest;
////	int	count; // kan sowieso weg
//	int	h;
//
//	h = half;
////	highest = half;
////	count = 0;
//	while (h)
//	{
//		if ((*stack_a)->sorted_index < half)
//		{
//			pb(stack_a, stack_b);
//			h--;
//		//	if ((*stack_b)->sorted_index < 125) // eerste 125 naar beneden bij 500
//		//		rb(stack_b);
//			//count = split_B(stack_b, count, highest); // houd 180 apart
//		}
//		else
//			ra(stack_a);
//	}
//	//organise_B(stack_a, stack_b, half);
//	organise(stack_a, stack_b);
//}
