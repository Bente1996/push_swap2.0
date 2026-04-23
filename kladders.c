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

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt al prima, al is 100 nummers wat slechter (net boven 700) dus gebruik niet altijd
//{
//	static 	int	arr[5] = {0};
//	int		half;
//	int		highest;
//	int		h;
//	int		operations;
//	int		count;
//
//	half = size / 2;
//	h = half;
//	highest = half;
//	count = 0;
//	while (h)
//	{
//		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
//		{
//			pb(stack_a, stack_b);
//			h--;		
//			if (*stack_b && in_group(*stack_b, arr, highest)) // als getal in de groep zit
//			{
//				highest = move_highest(arr, highest); // verander zoekcriteria op basis van group shift
//				if ((*stack_b)->next)
//					rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	while (count)
//	{
//		rrb(stack_b);
//		count--;
//	}
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}
