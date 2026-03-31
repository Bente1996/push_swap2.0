void	intentional_split(t_node **stack_a, t_node **stack_b, int half) // werkt
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

int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt
{
	int	half; // werkt gewoon ;p
	int	h;
	int	operations;

	half = size / 2;
	h = half;
	//while (size > half) // twee random stacks (kan optimaler door al r te doen)
	//{
	//	pb(stack_a, stack_b);
	//	size--;
	//}
	printf("%d\n", half);
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;
		}
		else
			ra(stack_a);
	}
	half--; // naar juiste index
	printf("Binnenkomst:\n");
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');
//	intentional_split(stack_a, stack_b, half);
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}

void	big_list(t_node **stack_a, t_node **stack_b, int half) // werkt met + 1
{
	int	whole;
	int	quarter;
	int	three_quarter;
	int	t_q;
	int	h;
	int	swap;
	int	swap_rot;

	whole = half * 2;
	quarter = half / 2;
	three_quarter = whole - quarter;
	t_q = three_quarter + 1;
	h = half + 1;
	swap = 0;
	swap_rot = 0;
	printf("Tussenstand:\n");
	printf("Halve:%d\n", half); // 49
	printf("Kwartje:%d\n", quarter); //24
	printf("TQ:%d\n", three_quarter); //74
	print_list(*stack_a, 'A');
	print_list(*stack_b, 'B');	
	while (*stack_a) // alles naar b: 73_50 0-49(random) 74_99
	{
		printf("t_q: %d\n", t_q);
		printf("h: %d\n", h);
		if (((*stack_a)->sorted_index  == t_q || ((*stack_a)->sorted_index == t_q + 1)) && (*stack_a)->sorted_index > three_quarter) // 75->99
		{
			if ((*stack_a)->sorted_index == t_q + 1)
			{
				pb(stack_a, stack_b);
				swap_rot++;
				t_q--; // blijf zoeken naar dezelfde
			}
			else if (swap_rot)
			{
				rrb(stack_b); // haal naar boven
				pb(stack_a, stack_b);
				rb(stack_b);
				swap_rot = 0;
				t_q++;
			}
			else
				pb(stack_a, stack_b);
			rb(stack_b);
			t_q++;
		}
		else if (((*stack_a)->sorted_index == h || ((*stack_a)->sorted_index == h + 1)) && (*stack_a)->sorted_index <= three_quarter) // 50->74
		{
			if ((*stack_a)->sorted_index == h + 1)
			{
				pb(stack_a, stack_b);
				swap++;
				h--; // h + 1 is al gevonden dus zal niet hierna gevonden worden
			}
			else if (swap)
			{
				pb(stack_a, stack_b);
				sb(stack_b);
				swap = 0;
				h++;
			}
			else
				pb(stack_a, stack_b);
			h++;
		}
		else
			ra(stack_a);
	}
	final_list(stack_a, stack_b, half, quarter);
}

void	shift_group(int *arr, int sum) // WerKT
{
	int	i;
	int	shrink;

	i = 0;
	shrink = 1;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
	{
		while (i + 1 < 5) // check 2, 3, 4
		{
			if (arr[i + 1])
				arr[i] = arr[i + 1] - (shrink * 9); // inhoud array 2 gaat naar array 1 100->10 bv
			else
				arr[i] = 0;
			i++;
			shrink *= 10;
		}
	}
	else if (sum == 11)
	{
		shrink = 1;
		while (i + 2 < 5) //  sla eerste twee over
		{
			if (arr[i + 2])
				arr[i] = arr[i + 2] - (shrink * 9);
			else
				arr[i] = 0;
			i++;
			shrink *= 10;
		}
	}
	else if (sum == 111)
	{
		shrink = 1;
		while (i + 3 < 5)
		{
			if (arr[i + 3])
				arr[i] = arr[i + 3] - (shrink * 9);
			else
				arr[i] = 0;
			i++;
			shrink *= 10;
		}
	}
	else if (sum == 1111)
	{
		shrink = 1;
		while (i + 4 < 5)
		{
			if (arr[i + 4])
				arr[i] = arr[i + 4] - (shrink * 9);
			else
				arr[i] = 0;
			i++;
			shrink *= 10;
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
