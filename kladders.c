void	intentional_split(t_node **stack_a, t_node **stack_b, int half)
{
	int	check; // maak check return van operations

	//print_list(*stack_a, 'A');
	//print_list(*stack_b, 'B');
	check = 1;

	if (one_element(stack_a, stack_b, half)) // alleen bij 2 of 3 elementen, maak aparte functies daarvoor
		return ;
	while (!sorted(*stack_a, half, 'A') || !sorted(*stack_b, half, 'B')) // zolang geen goed verdeelde stacks, gaat foutt wanneer b gesorteerd en a niet
	{
		if (one_element(stack_a, stack_b, half)) // toegevoegd bij "1 2 3 4", misschien niet nodig: voeg already_sorted() toe aan begin en ook weer bv bij big_list()
			return ;
		while (check && *stack_a && *stack_b && (*stack_a)->next && (*stack_b)->next) // rr
		{
			check = 0;
			while ((*stack_a)->sorted_index >= half && (*stack_b)->sorted_index < half) // check bij while loop hierboven = afdoende
			{
				rr(stack_a, stack_b);
				check++;
			}
			if ((*stack_a)->next->sorted_index >= half && (*stack_b)->sorted_index < half)
			{
				sa(stack_a);
				rr(stack_a, stack_b);
				check++;
			}
			else if ((*stack_b)->next->sorted_index < half && (*stack_a)->sorted_index >= half)
			{
				sb(stack_b);
				rr(stack_a, stack_b);
				check++;
			}
		} // verlaat wanneer geen rr mogelijkheid
		if (!sorted(*stack_a, half, 'A') && !sorted(*stack_b, half, 'B')) // wanneer beide nog niet gesorteerd zijn
		{
			if ((*stack_a)->sorted_index >= half)  // alleen A goed 
			{
				ra(stack_a);
				check++;
			}
			else if ((*stack_b)->sorted_index < half) // alleen B goed
			{
				rb(stack_b);
				check++;
			}
			else if (!check && stack_size(*stack_a) > stack_size(*stack_b)) // beide fout, push op basis van stack grootte
			{
				pb(stack_a, stack_b);
				check = 0;
			}
			else if (!check && stack_size(*stack_a) <= stack_size(*stack_b))
			{
				pa(stack_a, stack_b);
				check = 0;
			}
		}
		else if (one_element(stack_a,stack_b, half))
				return ;
		else if (sorted(*stack_a, half, 'A')) // als alleen a gesorteerd: elementen van a in b
		{
			while (!sorted(*stack_b, half, 'B'))
			{				
				if (one_element(stack_a,stack_b, half))
					return ;
				if ((*stack_b)->sorted_index < half)
					rb(stack_b);
				else 
					pa(stack_a, stack_b);
			}
		}
		else
		{
			while (!sorted(*stack_a, half, 'A'))
			{	
				if (one_element(stack_a,stack_b, half))
					return ;
				if ((*stack_a)->sorted_index >= half)
					ra(stack_a);
				else 
					pb(stack_a, stack_b);
			}
		}
	}
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 100 nummers 1200 operations
{ 
	int	lower; 
	int	swap;
	int	bottom;
	t_node	*bottom_stack = NULL;

	lower = half;
	swap = 0;
	bottom = 0;

	while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	half++; // kan dit  optimaler? maakt wss heel weinig uit
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	while (*stack_b) // kan optimaler
	{
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1) // als 48 of 49 gevonden
		{
			if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
			{
				pa(stack_a, stack_b);
				swap++;
				lower++; // houdt originele getal aan
			}
			else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				lower--; // 49 -> 47
			}
			else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
				pa(stack_a, stack_b);
			lower--;
			if (bottom && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
			{
				while (bottom)
				{
					rra(stack_a);
					lower--;
					bottom--;
				}
				if ((*stack_a)->sorted_index > (*stack_a)->next->sorted_index) // 49, 48, 46 ,47: sa
					sa(stack_a);
				bottom_stack = NULL;
				bottom = 0;
			}
		}
		else if (((*stack_b)->sorted_index == (*stack_a)->sorted_index - 2 || (*stack_b)->sorted_index == (*stack_a)->sorted_index - 3) && bottom < 2)
		{
			pa(stack_a, stack_b);
			if (!bottom || (*stack_a)->sorted_index > bottom_stack->sorted_index) // bottom_stack == grootste index
				bottom_stack = find_bottom(*stack_a);
			ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
			bottom++;
		}
		else// niks interessants gevonden
		{
			printf("LOWER: %d\n", lower);
			printf("stack_b: %d\n", (*stack_b)->sorted_index);
			rb(stack_b);
		}
		if (bottom && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
		{
			while (bottom)
			{
				rra(stack_a);
				lower--;
				bottom--;
			}
			if ((*stack_a)->sorted_index > (*stack_a)->next->sorted_index) // 49, 48, 46 ,47: sa
				sa(stack_a);
			bottom_stack = NULL;
			bottom = 0;
		}
	}
	//while (*stack_b && half)
	//{
	//	while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
	//	{
	//		rrb(stack_b);
	//		pa(stack_a, stack_b);
	//		half--;
	//	}
	//	half++; // kan dit  optimaler? maakt wss heel weinig uit
	//	while (half)
	//	{
	//		pa(stack_a, stack_b);
	//		half--;
	//	}
	//	while (*stack_b) // kan optimaler
	//	{
	//		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
	//		{
	//			if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
	//			{
	//				pa(stack_a, stack_b);
	//				swap++;
	//				lower++;
	//			}
	//			else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
	//			{
	//				pa(stack_a, stack_b);
	//				sa(stack_a);
	//				swap = 0;
	//				if (bottom)
	//				{
	//					rra(stack_a);
	//					bottom_stack = NULL;
	//					bottom = 0;
	//					lower--;
	//				}
	//				lower--;
	//			}
	//			else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
	//			{
	//				pa(stack_a, stack_b);
	//				if (bottom && bottom_stack->sorted_index == lower - 1)
	//				{
	//					rra(stack_a);
	//					bottom_stack = NULL;
	//					bottom = 0;
	//					lower--;
	//				}
	//			}
	//			lower--;
	//		}
	//		else if ((*stack_b)->sorted_index == lower - 2 && !bottom)
	//		{
	//			pa(stack_a, stack_b);
	//			ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
	//			bottom_stack = find_bottom(*stack_a);
	//			bottom = 1;
	//		}
	//		else
	//			rb(stack_b);
	//	}
	//}
}

//void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 100 nummers 1200 operations
//{
//	int	lower;
//	int	swap;
//	int	bottom;
//	t_node	*bottom_stack = NULL;
//
//	lower = half;
//	swap = 0;
//	bottom = 0;
//	printf("LOWER:%d\n", lower);
//	while (*stack_b && half)
//	{
//		while (half > quarter) // kan in 1 loop: alleen half en kijk naar index voor rrb of niet, quarter = 24 lower = 49
//		{
//			rrb(stack_b);
//			pa(stack_a, stack_b);
//			half--;
//		}
//		half++; // kan dit  optimaler? maakt wss heel weinig uit
//		while (half)
//		{
//			pa(stack_a, stack_b);
//			half--;
//		}
//		while (*stack_b) // kan optimaler
//		{
//			if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
//			{
//				if ((*stack_b)->sorted_index == lower - 1) // verkeerde bovenaan
//				{
//					pa(stack_a, stack_b);
//					swap++;
//				}
//				else if (swap) // goede gevonden, zet eronder, lijst klopt, als bottom: zet boven
//				{
//					pa(stack_a, stack_b);
//					sa(stack_a);
//					swap = 0;
//					lower--;
//					if (bottom)
//					{
//						if ((bottom  == 1) && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1))
//						{
//							rra(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower--;
//						}
//						else if (bottom == 2)
//						{
//							if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // verwijder dubbele operaties ff
//							{
//								rra(stack_a);
//								rra(stack_a);
//								sa(stack_a);
//								bottom_stack = NULL;
//								bottom = 0;
//								lower -= 2;
//							}
//							else
//							{
//								rra(stack_a);
//								rra(stack_a);
//								bottom_stack = NULL;
//								bottom = 0;
//								lower -= 2;
//							}
//						}
////						if (bottom_stack->next) // als 2 onderaan, zet beide boven en swap
////						{
////							swap = 1;
////							rra(stack_a);
////							lower--;
////						}
////						rra(stack_a);
////						if (swap)
////							sa(stack_a);
////						swap = 0;
////						bottom_stack = NULL;
////						bottom = 0;
////						lower--;
//						}
//				}
//				else // lijst klopt, gewoon 1 erbij, check of bottom aansluit
//				{
//					pa(stack_a, stack_b);
//					if ((bottom  == 1) && (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1)) // eentje onder, zet boven wanneer goed
//					{
//						rra(stack_a);
//						bottom_stack = NULL;
//						bottom = 0;
//						lower--;
//					}
//					else if (bottom == 2)
//					{
//						if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // verwijder dubbele operaties ff
//						{
//							rra(stack_a);
//							rra(stack_a);
//							sa(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower -= 2;
//						}
//						else
//						{
//							rra(stack_a);
//							rra(stack_a);
//							bottom_stack = NULL;
//							bottom = 0;
//							lower -= 2;
//						}
//					}
//					lower--;
//				}
//			}
//			else if ((*stack_b)->sorted_index == lower - 2 && bottom < 2)
//			{
//				if (bottom == 1 && (*stack_b)->sorted_index == bottom_stack->sorted_index - 1)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a); // zet onderaan A tot ie boven kan aansluiten
//					bottom++;
//				}
//				else if (!bottom)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom_stack = find_bottom(*stack_a);
//					bottom++;
//				}
//			}
//			else if ((*stack_b)->sorted_index == lower - 3 && bottom < 2)
//			{
//				if (bottom == 1 && (*stack_b)->sorted_index == bottom_stack->sorted_index + 1)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom++;
//				}
//				else if (!bottom)
//				{
//					pa(stack_a, stack_b);
//					ra(stack_a);
//					bottom_stack = find_bottom(*stack_a);
//					bottom++;
//				}
//			}
//			else
//				rb(stack_b);
//		}
//	}
//}

