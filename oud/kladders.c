void	sort_big(t_node **stack_a, t_node **stack_b, int all)
{
	int 	sorted;
	int	half = all / 2;

	sorted = half - 180; // - size
	organise_B(stack_a, stack_b, half);
	if (all != half * 2)
	{
		organise_A(stack_a, stack_b, half + 180, half + 1);
		grow_list(stack_b, stack_a, half * 2 + 1, half - 179);
		sorted++;
	}
	else
	{
		organise_A(stack_a, stack_b, half + 180, half);
		grow_list(stack_b, stack_a, half * 2, half - 180);
	}
	while (sorted--)
	{
		pa(stack_a, stack_b);
		if (*stack_a)
			ra(stack_a);
	}
	grow_list(stack_a, stack_b, half + 180, 180);
	grow_list(stack_a, stack_b, half, half);
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

void	sort_highest(t_node **stack_a, t_node **stack_b, int highest) // gemaakt voor 225, minder optimaal dan 180
{
	int	count;

	count = 25;
	printf("highest:%d\n", highest);
	while (count)
	{
		count--;
		if ((*stack_b)->sorted_index > (highest - 231)) // 20-25 goed
		{
			printf("A: %d\n", (*stack_b)->sorted_index);
			rb(stack_b);
		}
		else if ((*stack_b)->sorted_index > (highest - 236)) // 15-20 bijna goed
			pa(stack_a, stack_b);
		else
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
	}
	count = 5;
	while (count)
	{
		pb(stack_a, stack_b);
		count--;
	}
	count = 5;
	while (count)
	{
		rb(stack_b); // 15-20 goed
		count--;
	}
	count = 15;
	printf("highest %d\n", highest);
	printf("highest - 236 %d\n", highest - 246);
	while (count)
	{
		rra(stack_a);
		if ((*stack_a)->sorted_index > (highest - 246)) // 5-15
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > (highest - 241)) // 10-15
				rb(stack_b);
		}
		count--;
	}
	count = 5;
	while (count)
	{
		count--;
		rb(stack_b); // 5-10
	}
	count = 5;
	while (count)
	{
		pb(stack_a, stack_b);
		count--;
	}
	count = 5;
	while (count)
	{
		count--;
		rb(stack_b); // 0-5
	}
}

void	halve(t_node **stack_a, t_node **stack_b, int size) // 225 uitgewerkt met extra functie, minder optimaal dan 180
{
	int		highest;

	highest = size / 2;
	low_to_A(stack_a, stack_b, highest); // split en houdt 135 apart, 115-249 bovenaan B
	split_group(stack_a, stack_b, highest, 225); // 0-180 beneden
	highest -= 135;
	sort_high(stack_a, stack_b, highest); 
	sort_medium(stack_a, stack_b, highest); 
	sort_lowest(stack_a, stack_b, highest);
	int count = 45; // gesorteerd naar beneden, 25 over
	while (count)
	{
		rb(stack_b);
		count--;
	}
	highest += 135;
	sort_highest(stack_a, stack_b, highest); // sort 25 leftovers
	split_group(stack_a, stack_b, highest, 180); // 0-135 beneden
	highest -= 90;
	sort_high(stack_a, stack_b, highest); 
	sort_medium(stack_a, stack_b, highest); 
	sort_lowest(stack_a, stack_b, highest);
	count = 115; // doe juist 115 rb ipv 135 rrb
	while (count)
	{
		rb(stack_b);
		count--;
	}
	highest += 90;
	split_group(stack_a, stack_b, highest, 135); // 0-90 beneden
	highest -= 45;
	sort_high(stack_a, stack_b, highest); 
	sort_medium(stack_a, stack_b, highest); 
	sort_lowest(stack_a, stack_b, highest);
	count = 90;
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	highest += 45;
	split_group(stack_a, stack_b, highest, 90); // 45 beneden
	sort_high(stack_a, stack_b, highest);
	sort_medium(stack_a, stack_b, highest);
	sort_lowest(stack_a, stack_b, highest);
	sort_rest(stack_a, stack_b, highest); // sorteert laatste 45
}

int	random_split(t_node **stack_a, t_node **stack_b, int size) // goed bij 500, bij 100 aanpassen (niet 45x rrb aan begin, maar 5x rb) 
{
	int		half;
	int		highest;
	int		h;
	int		operations;
	int		count;

	half = size / 2;
	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;	
			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 91) // -1 tot -90
			{
				if ((*stack_b)->next)
					rb(stack_b);
				count++;
			}
		}
		else
			ra(stack_a);
	}
	while (count) // alles naar boven
	{
		rrb(stack_b);
		count--;
	}
	count = 90;
	while (count)
	{
		if ((*stack_b)->sorted_index > highest - 46) // -1 tot -45 naar beneden voor later
			rb(stack_b);
		else if ((*stack_b)->sorted_index < highest - 60) // -61 tot -90 bovenaan A
			pa(stack_a, stack_b);
		else                                             // -46 tot -60 onderaan A
		{
			pa(stack_a,stack_b);
			ra(stack_a);
		}
		count--;
	}
	count = 30;
	while (count)
	{
		if ((*stack_a)->sorted_index > highest - 76) // -61 tot -75 onderaan A
			ra(stack_a);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(stack_b);
		}
		count--;
	}
	count = 10;
	while (count) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->sorted_index > highest - 81) // -76 tot -80 naar A
			pa(stack_a, stack_b);
		count--;
	}
	count = 5;
	while (count) // -76 tot -80 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}
	count = 15;
	while (count)
	{
		rra(stack_a); // alles naaar boven
		count--;
	
	}
	count = 15;
	while (count) // -61 tot -75 op goeie plek zetten
	{
		if ((*stack_a)->sorted_index < highest - 65) // -66 tot -75 naar B
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(stack_b);
		}
		else // -61 tot -65 onderaan A
		     ra(stack_a);
		count--;
	}
	count = 5;
	while (count)
	{
		rrb(stack_b); // -66 tot -70 op goeie plek zetten
		count--;
	}
	count = 5;
	while (count)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
		count--;
	}
	count = 15;
	while (count) // -46 tot -60 op goeie plek zetten
	{
		rra(stack_a); // alles naar boven
		if ((*stack_a)->sorted_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(stack_a, stack_b); // -56 tot -60 staat goed
			if ((*stack_b)->sorted_index > highest - 56) // -51 tot -55 naar beneden
				rb(stack_b);
		}
		count--;
	}
	count = 5;
	while (count) // -51 tot -55 op goeie plek zetten
	{
		rrb(stack_b);
		count--;
	}
	count = 5;
	while (count) // -46 tot -50 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}


				// -1 tot -45 deel (goed)
	int one = 0; // 15
	int two = 0; // 15
	count = 45;
	while (count)
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		count--;
		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			one++;
		}
		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
		{
			pa(stack_a, stack_b);
			two++;
		}
	}
	int three = 15;
	while (three)
	{
		if ((*stack_b)->sorted_index >= highest - 35) // -31 tot -35
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index >=highest - 40) // -36 tot -40
			rb(stack_b);
		else // -41 tot -45
		     pa(stack_a, stack_b);
		three--;
	}
	three = 5;
	while (three)
	{
		pb(stack_a, stack_b); // -41 tot -45 goed
		three--;
	}
	three = 5;
	while (three)
	{
		rrb(stack_b); // -36 tot -40 goed
		three--;
	}
	three = 5;
	while (three)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -30 tot -35 goed
		three--;
	}
	while (two)
	{
		if ((*stack_a)->sorted_index >= highest - 20)  // -16 tot -20
			ra(stack_a);
		else if ((*stack_a)->sorted_index >= highest - 25) // -21 tot -25
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else // -26 tot -30
		     pb(stack_a, stack_b); // staat nu al goed
		two--;
	}
	two = 5;
	while (two)
	{
		rrb(stack_b); // -21 tot -25 goed
		two--;
	}
	two = 5;
	while (two)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -16 tot -20 goed
		two--;
	}
	while (one)
	{
		rra(stack_a); // -1 tot -5
		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
				rb(stack_b);
		}
		one--;
	}
	one = 5;
	while (one)
	{
		rrb(stack_b); // -6 tot -10 goed
		one--;
	}
	one = 5;
	while (one)
	{
		pb(stack_a, stack_b); // -1 tot -5 goed
		one--;
	}
	half--; // naar juiste index
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}

int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt al prima, al is 100 nummers wat slechter (net boven 700) dus gebruik niet altijd
{
	static 	int	arr[5] = {0};
	int		half;
	int		highest;
	int		h;
	int		operations;
	int		count;

	half = size / 2;
	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;		
			if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
			{
				highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
				if ((*stack_b)->next)
					rb(stack_b);
				count++;
			}
		}
		else
			ra(stack_a);
	}
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	half--; // naar juiste index
	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	operations = count_operations("");
	return (operations);
}

int	find_highest(t_node *stack_b)
{
	int	pos;
	int	highest_pos;
	t_node	*highest;

	pos = 1;
	highest_pos = 1;
	highest = stack_b;
	while (stack_b)
	{
		if (stack_b->value > highest->value)
		{
			highest = stack_b;
			highest_pos = pos;
		}
		stack_b = stack_b->next;
		pos++;
	}
	return (highest_pos);
}

void	highest_to_top(t_node **stack_b)
{
	int	mid_stack;
	int	highest_pos;

	highest_pos = find_highest(*stack_b);
	mid_stack = stack_size(*stack_b) / 2;
	if (mid_stack < highest_pos) // van onderaan
	{
		while (highest_pos <= stack_size(*stack_b))
		{
			rrb(stack_b);
			highest_pos++;
		}
	}
	else // vanaf boven
	{
		while (highest_pos > 1)
		{
			rb(stack_b);
			highest_pos--;
		}
	}
}

t_node	*sort_three(t_node **stack_a, t_node **stack_b)
{
	if ((*stack_b)->sorted_index == 1)
		rb(stack_b);
	if ((*stack_b)->sorted_index == 3) // 321  312
	{
		pa(stack_a, stack_b);
		pa(stack_a, stack_b);
		pa(stack_a, stack_b);
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
	}
	else if ((*stack_b)->sorted_index == 2) // 
	{
		pa(stack_a, stack_b);
		if ((*stack_b)->sorted_index == 1)
			sb(stack_b);
		pa(stack_a, stack_b);
		sa(stack_a);
		pa(stack_a, stack_b);
	}
	return (*stack_a);
}

t_node	*sort_top(t_node **stack_a, t_node **stack_b) // selection sort
{
	int n;

	n = 25;
	printf("SORT TOP\n");
	while (n) // voeg functies voor kleine aantallen toe
	{
		if (n == 3)
		{
			*stack_a = sort_three(stack_a, stack_b);
			break ;
		}
		highest_to_top(stack_b);
		pa(stack_a, stack_b);
		n--;
	}
	return (*stack_a);
}

// final_list lang met commentaar over verkleinde functies:

		///////////
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1) // == case_one()
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom) // == handle_bottom()
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2    // == more_bottom()
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook // == add_second()
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3 // == try_three()
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede // == try_two()
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek // == check_third() (nog maken)
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //niet 2 juist, bottom mag als tweede // == get_second () nog maken
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // 2e was niet goed
										ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal) // == get_third()
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index) // zet hoogste als bottom
											bottom_stack = *stack_a;
										ra(stack_a); // twee beneden
									}
								}		
							}										
						}
						else // geen bottom over
						     bottom_stack = NULL;
					}
				}
				lower--;
			}
			else // == lower maar geen swap
			{
				pa(stack_a, stack_b);
				if (bottom) // maak 6 switch
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //2e niet juist, bottom mag als tweede
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // er waren er maar twee
									     ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index)
											bottom_stack = *stack_a;
										ra(stack_a);
									}
								}		
							}										
						}
						else // was geen bottom over
						     bottom_stack = NULL;
					}
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 4 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else
			rb(stack_b);
	}
}


// final_list lange versie:

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // EINDRESULTAAT,ONOPGREBROKEN
																			  // VERSIE,
																			  // WERKT!!!
{
	t_node	*bottom_stack;
	int	lower;
	int	swap;
	int	bottom;

	lower = half + 1;
	swap = 0;
	bottom = 0;
	bottom_stack = NULL;
	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
	while (*stack_b)
	{
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom) // maak 6 switch
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //niet 2 juist, bottom mag als tweede
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // 2e was niet goed
										ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index) // zet hoogste als bottom
											bottom_stack = *stack_a;
										ra(stack_a); // twee beneden
									}
								}		
							}										
						}
						else // geen bottom over
						     bottom_stack = NULL;
					}
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom) // maak 6 switch
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er 1 of 2
						{
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								bottom_stack = find_bottom(*stack_a); // deze is onder
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // tweede mag ook
								{
									rra(stack_a); // tweede naar boven
									bottom--; // 0 of 1 over
									lower--;
									if (bottom) // als er 3 waren
										bottom_stack = find_bottom(*stack_a); // de laatste
									else
										bottom_stack = NULL; // er waren er maar 2 [CASE 0.1]
									if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // perfect rijtje [CASE 1]
									{
										rra(stack_a);
										bottom--;
										bottom_stack = NULL;
										lower--;
									} // else: 3e was niet goed [CASE 1 fout]
								}
								else if (bottom == 2) // tweede mag niet, maar zijn er 3
								{
									bottom_stack = check_bottom(*stack_a); // vind hoogste van de twee // maak functie: pak een na laatste
									if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e mag
									{
										rra(stack_a);
										rra(stack_a); // 2 naar boven en swap
										sa(stack_a);
										lower--;
										bottom--;
									}
									if ((*stack_a)->sorted_index != (*stack_a)->next->sorted_index - 1) // check of 2e nu wel goed is
									{
										ra(stack_a); // stuur terug als bovenste fout [CASE 2 fout]
										bottom_stack = find_bottom(*stack_a);
									}
									else // nu wel goed rijtje [CASE 2]
									{
										bottom--; // naar 0
										bottom_stack = NULL;
										lower--;
									}
								} // else: bottom == 1 == [case 0.2]
							}
							else // eerste was niet goed , dus probeer tweede
							{
								rra(stack_a); // tweede naar boven
								if (bottom == 2)
									bottom_stack = find_bottom(*stack_a); // check 3e getal
								else
									bottom_stack = (*stack_a)->next; // als er maar 2 getallen waren, wordt 2 bottom
								if ((*stack_a)->sorted_index == (*stack_a)->next->next->sorted_index - 1) // als tweede goed is
								{
									sa(stack_a); // tweede op goede plek
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 getallen op juiste plek
									{
										lower--;
										bottom--; // bottom == 1
										if (bottom) // als 3 getallen
										{
											if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // als 3e aansluit [CASE 3]
											{
												rra(stack_a); // haal 3e op
												bottom_stack = NULL;
												bottom--; // bottom op 0
												lower--;
											}// else: 3e sluit niet aan [CASE 3 fout], bottom op 1
										}
										else
											bottom_stack = NULL; // maar 2 getallen [CASE 0.3]
									}	
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) //2e niet juist, bottom mag als tweede
									{
										rra(stack_a); // haal bottom naar boven, 3 boven
										lower--;
										bottom--; // bottom 1
										sa(stack_a); // twee getallen erop geplakt, 2 iig goed
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // goed rijtje [CASE: 5]
										{
											lower--;
											bottom--; // bottom naar 0
											bottom_stack = NULL;
										}
										else // fout rijtje [CASE: 5 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // eentje over op bodem
										}
									}
									else // er waren er maar twee
									     ra(stack_a);
								}
								else // tweede was niet goed, dus moet wel derde zijn (en dus 3 in totaal)
								{
									rra(stack_a); // haal derde op
									sa(stack_a);
									ra(stack_a); // eentje eraf
									sa(stack_a); // 3e zit goed aangesloten					
									bottom_stack = find_bottom(*stack_a);
									if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // 2 op goede plek
									{
										bottom--;
										lower--;
										if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // [CASE 4]
										{
											rra(stack_a);
											bottom--; // gaat naar 0
											lower--;
											bottom_stack = NULL;
										} // else: [CASE 4 fout]
									}
									else if (bottom_stack->sorted_index == (*stack_a)->next->sorted_index - 1) // bottom mag aansluiten als tweede
									{
										rra(stack_a); // haal bottom omhoog
										sa(stack_a);
										lower--;
										bottom--;
										if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // perfect rijtje [CASE: 6]
										{
											bottom--;
											lower--;
											bottom_stack = NULL; // alles naar 0
										}
										else // bovenste past niet [CASE: 6 fout]
										{
											ra(stack_a);
											bottom_stack = find_bottom(*stack_a); // zet bottom juist
										}
									}
									else // er was er maar 1 vd 3 goed
									{
										if ((*stack_a)->sorted_index > bottom_stack->sorted_index)
											bottom_stack = *stack_a;
										ra(stack_a);
									}
								}		
							}										
						}
						else // was geen bottom over
						     bottom_stack = NULL;
					}
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 4 && bottom < 3)
		{
			if (!bottom || bottom_stack->sorted_index < (*stack_b)->sorted_index)
			{
				pa(stack_a, stack_b);
				ra(stack_a);
				bottom_stack = find_bottom(*stack_a);
			}
			else
			{
				pa(stack_a, stack_b);
				ra(stack_a);
			}
			bottom++;
		}
		else
			rb(stack_b);
	}
}
// eerste versies final_list:

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 2 bottom: WERKT :D
{
	t_node	*bottom_stack;
	int	lower;
	int	swap;
	int	bottom;

	lower = half + 1;
	swap = 0;
	bottom = 0;
	bottom_stack = NULL;
	while (half > quarter)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	int n = 15000;
	while (*stack_b && n)
	{
		printf("stack_A: %d\n", (*stack_a)->sorted_index);
		if (bottom_stack)
			printf("bottom:%d  %d\n", bottom_stack->sorted_index, bottom);
		printf("stack_B: %d\n", (*stack_b)->sorted_index);
		printf("lower: %d\n", lower);
		printf("swap:%d\n", swap);
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom)
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er twee
						{
							bottom_stack = find_bottom(*stack_a); // deze is over
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // beiden goed
								{
									rra(stack_a); // tweede naar boven
									bottom--; // naar 0
									bottom_stack = NULL;
									lower--;
								}
							}
							else // eerste was niet goed , dus tweede wel
							{
								rra(stack_a);
								sa(stack_a);
								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed  ( != )
								{
									ra(stack_a);
									bottom_stack = find_bottom(*stack_a);
								}
								else
								{
									bottom--; // naar 0
									bottom_stack = NULL; // beiden goed
									lower--;
								}
							}
						}
					}
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom)
				{
					if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // iig 1 moet naar boven
					{
						rra(stack_a); // eerste naar boven
						bottom--;
						lower--;
						if (bottom) // zijn er twee
						{
							bottom_stack = find_bottom(*stack_a);
							if ((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1) // eerste was goed
							{
								if (bottom_stack->sorted_index == (*stack_a)->sorted_index - 1) // beiden goed
								{
									rra(stack_a); // tweede naar boven
									bottom--; // naar 0
									bottom_stack = NULL;
									lower--;
								}
							}
							else // eerste was niet goed , dus tweede wel
							{
								rra(stack_a);
								sa(stack_a);
								if (!((*stack_a)->sorted_index == (*stack_a)->next->sorted_index - 1)) // check of beiden goed ( != )
								{
									ra(stack_a);
									bottom_stack = find_bottom(*stack_a);
								}
								else
								{
									bottom--; // naar 0
									bottom_stack = NULL; // beiden goed
									lower--;
								}
							}
						}
					}
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && bottom < 2)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index) // bottom_stack = grootste index
				bottom_stack = find_bottom(*stack_a);
			bottom++;
		}
		else if ((*stack_b)->sorted_index == lower - 3 && bottom < 2)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			if (!bottom || bottom_stack->sorted_index < bottom_stack->next->sorted_index)
				bottom_stack = find_bottom(*stack_a);
			bottom++;
		}
		else
			rb(stack_b);
		n--;
	}
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // 1 bottom: WERKT
{
	t_node	*bottom_stack;
	int	lower;
	int	swap;
	int	bottom;

	lower = half + 1;
	swap = 0;
	bottom = 0;
	bottom_stack = NULL;
	while (half > quarter)
	{
		rrb(stack_b);
		pa(stack_a, stack_b);
		half--;
	}
	while (half)
	{
		pa(stack_a, stack_b);
		half--;
	}
	int n = 100000;
	while (*stack_b && n)
	{
		printf("stack_B: %d\n", (*stack_b)->sorted_index);
		printf("lower: %d\n", lower);
		if ((*stack_b)->sorted_index == lower || (*stack_b)->sorted_index == lower - 1)
		{
			if ((*stack_b)->sorted_index == lower - 1)
			{
				pa(stack_a, stack_b);
				swap++;
				lower++;
			}
			else if (swap)
			{
				pa(stack_a, stack_b);
				sa(stack_a);
				swap = 0;
				if (bottom)
				{
					rra(stack_a);
					bottom = 0;
					bottom_stack = NULL;
					lower--;
				}
				lower--;
			}
			else
			{
				pa(stack_a, stack_b);
				if (bottom && bottom_stack->sorted_index == (*stack_a)->sorted_index - 1)
				{
					rra(stack_a);
					bottom = 0;
					bottom_stack = NULL;
					lower--;
				}
			}
			lower--;
		}
		else if ((*stack_b)->sorted_index == lower - 2 && !bottom)
		{
			pa(stack_a, stack_b);
			ra(stack_a);
			bottom = 1;
			bottom_stack = find_bottom(*stack_a);
		}
		else
			rb(stack_b);
		n--;
	}
}

//OUDE WERKENDE VERSIE FUNCTIES (big_list + final_list)

void	sort_all(t_node **stack_a, t_node **stack_b, int half) // 180 werkend
{
	split_list(stack_a, stack_b, half); // split en houdt 135 apart, 115-249 bovenaan B
	big_list(stack_a, stack_b, --half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
	final_list(stack_a, stack_b, half, half / 2);
}

void	final_list(t_node **stack_a, t_node **stack_b, int half, int quarter) // werkt normaal
{
	t_stats	*data;
	int	n;

//	sorted_to_A(stack_a, stack_b, half, quarter); // alles bovenaan en onderaan B wat gesorteerd was naar A pushen
	half--; // voor method 2
	half--; // voor method 2
	quarter++; // voor method 2
	quarter--;
	data = alloc_stats(stack_a, stack_b, half);
	if (!data)
		return ;
	while (data->stack_b)
	{
		n = find_case(data->stack_b->sorted_index, data->lower, data->bottom);
		if (n == 1)
		{
			case_one(data);
		}
		else if (n == 2) // for -2, -3 en -4 (bottom <3)
		{
			case_two(data);
		}
		else // rest
			rb(&data->stack_b);
		*stack_a = data->stack_a;
		*stack_b = data->stack_b;
	}
}

