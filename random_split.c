#include "push_swap.h"
#include <stdio.h>


//int	random_split(t_node **stack_a, t_node **stack_b, int size) // goed bij 500, bij 100 aanpassen (niet 45x rrb aan begin, maar 5x rb) 
//{
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
//			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 181) // -1 tot -181 (was -1 tot -135) // 180 IS GROTER DAN 125 (250/2), IPV NAAR BENEDEN, DOE REST NAAR BENEDEN!! /git test
//			{
//				if ((*stack_b)->next)
//					rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//
//
//															// -136 tot -180
//															// (kopie)
//	while (count) // alles naar boven
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 180;
//	while (count)
//	{
//		if ((*stack_b)->sorted_index > highest - 136) // -1 tot -135 naar beneden voor later
//			rb(stack_b);
//		else if ((*stack_b)->sorted_index < highest - 150) // -151 tot -180 bovenaan A
//			pa(stack_a, stack_b);
//		else                                             // -136 tot -150 onderaan A
//		{
//			pa(stack_a,stack_b);
//			ra(stack_a);
//		}
//		count--;
//	}
//	count = 30;
//	while (count)
//	{
//		if ((*stack_a)->sorted_index > highest - 166) // -151 tot -165 onderaan A
//			ra(stack_a);
//		else                                       // -166 tot -180 bovenaan B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 176) // -166 tot -175 naar beneden, -176 tot -180 al goed!
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 10;
//	while (count) // -171 tot -175 op goeie plek zen
//	{
//		rrb(stack_b);
//		if ((*stack_b)->sorted_index > highest - 171) // -166 tot -170 naar A
//			pa(stack_a, stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -166 tot -170 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//	count = 15;
//	while (count)
//	{
//		rra(stack_a); // alles naaar boven
//		count--;
//	
//	}
//	count = 15;
//	while (count) // -151 tot -165 op goeie plek zetten
//	{
//		if ((*stack_a)->sorted_index < highest - 155) // -156 tot -165 naar B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 161) // -156 tot -160 onderaan B, -161 tot -165 op goeie plek
//				rb(stack_b);
//		}
//		else // -151 tot -155 onderaan A
//		     ra(stack_a);
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rrb(stack_b); // -156 tot -160 op goeie plek zetten
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -151 tot -155 op goeie plek zetten
//		count--;
//	}
//	count = 15;
//	while (count) // -136 tot -150 op goeie plek zetten
//	{
//		rra(stack_a); // alles naar boven
//		if ((*stack_a)->sorted_index < highest - 150) // -151 tot -150 op goeie plek zetten
//		{
//			pb(stack_a, stack_b); // -146 tot -150 staat goed
//			if ((*stack_b)->sorted_index > highest - 146) // -141 tot -145 naar beneden
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 5;
//	while (count) // -141 tot -145 op goeie plek zetten
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -136 tot -140 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//	print_list(*stack_b, 'B');
//															// -91 tot -135
//															// (kopie)
//	count = 135;
//	while (count) // alles naar boven
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 135;
//	while (count)
//	{
//		if ((*stack_b)->sorted_index > highest - 91) // -1 tot -90 naar beneden voor later
//			rb(stack_b);
//		else if ((*stack_b)->sorted_index < highest - 105) // -106 tot -135 bovenaan A
//			pa(stack_a, stack_b);
//		else                                             // -91 tot -105 onderaan A
//		{
//			pa(stack_a,stack_b);
//			ra(stack_a);
//		}
//		count--;
//	}
//	count = 30;
//	while (count)
//	{
//		if ((*stack_a)->sorted_index > highest - 121) // -106 tot -120 onderaan A
//			ra(stack_a);
//		else                                       // -121 tot -135 bovenaan B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 131) // -121 tot -130 naar beneden, -131 tot -135 al goed!
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 10;
//	while (count) // -126 tot -130 op goeie plek zen
//	{
//		rrb(stack_b);
//		if ((*stack_b)->sorted_index > highest - 126) // -121 tot -125 naar A
//			pa(stack_a, stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -121 tot -125 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//	count = 15;
//	while (count)
//	{
//		rra(stack_a); // alles naaar boven
//		count--;
//	
//	}
//	count = 15;
//	while (count) // -106 tot -120 op goeie plek zetten
//	{
//		if ((*stack_a)->sorted_index < highest - 110) // -111 tot -120 naar B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 116) // -111 tot -115 onderaan B, -116 tot -120 op goeie plek
//				rb(stack_b);
//		}
//		else // -106 tot -110 onderaan A
//		     ra(stack_a);
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rrb(stack_b); // -111 tot -115 op goeie plek zetten
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -106 tot -110 op goeie plek zetten
//		count--;
//	}
//	count = 15;
//	while (count) // -91 tot -105 op goeie plek zetten
//	{
//		rra(stack_a); // alles naar boven
//		if ((*stack_a)->sorted_index < highest - 95) // -96 tot -105 op goeie plek zetten
//		{
//			pb(stack_a, stack_b); // -101 tot -105 staat goed
//			if ((*stack_b)->sorted_index > highest - 101) // -96 tot -100 naar beneden
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 5;
//	while (count) // -96 tot -100 op goeie plek zetten
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -91 tot -95 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//
//
//
//
//											// -46 tot -90
//	count = 90;
//	while (count) // alles naar boven
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 90;
//	while (count)
//	{
//		if ((*stack_b)->sorted_index > highest - 46) // -1 tot -45 naar beneden voor later
//			rb(stack_b);
//		else if ((*stack_b)->sorted_index < highest - 60) // -61 tot -90 bovenaan A
//			pa(stack_a, stack_b);
//		else                                             // -46 tot -60 onderaan A
//		{
//			pa(stack_a,stack_b);
//			ra(stack_a);
//		}
//		count--;
//	}
//	count = 30;
//	while (count)
//	{
//		if ((*stack_a)->sorted_index > highest - 76) // -61 tot -75 onderaan A
//			ra(stack_a);
//		else                                       // -76 tot -90 bovenaan B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 10;
//	while (count) // -81 tot -85 op goeie plek zetten
//	{
//		rrb(stack_b);
//		if ((*stack_b)->sorted_index > highest - 81) // -76 tot -80 naar A
//			pa(stack_a, stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -76 tot -80 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//	count = 15;
//	while (count)
//	{
//		rra(stack_a); // alles naaar boven
//		count--;
//	
//	}
//	count = 15;
//	while (count) // -61 tot -75 op goeie plek zetten
//	{
//		if ((*stack_a)->sorted_index < highest - 65) // -66 tot -75 naar B
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
//				rb(stack_b);
//		}
//		else // -61 tot -65 onderaan A
//		     ra(stack_a);
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rrb(stack_b); // -66 tot -70 op goeie plek zetten
//		count--;
//	}
//	count = 5;
//	while (count)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
//		count--;
//	}
//	count = 15;
//	while (count) // -46 tot -60 op goeie plek zetten
//	{
//		rra(stack_a); // alles naar boven
//		if ((*stack_a)->sorted_index < highest - 50) // -51 tot -60 op goeie plek zetten
//		{
//			pb(stack_a, stack_b); // -56 tot -60 staat goed
//			if ((*stack_b)->sorted_index > highest - 56) // -51 tot -55 naar beneden
//				rb(stack_b);
//		}
//		count--;
//	}
//	count = 5;
//	while (count) // -51 tot -55 op goeie plek zetten
//	{
//		rrb(stack_b);
//		count--;
//	}
//	count = 5;
//	while (count) // -46 tot -50 op goeie plek zetten
//	{
//		pb(stack_a, stack_b);
//		count--;
//	}
//
//
//				// -1 tot -45 deel (goed)
//	int one = 0; // 10
//	int two = 0; // 10
//	count = 45;
//	while (count)
//	{
//		rrb(stack_b); // -31 tot -45 blijft in B
//		count--;
//		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			one++;
//		}
//		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
//		{
//			pa(stack_a, stack_b);
//			two++;
//		}
//	}
//	int three = 15;
//	while (three)
//	{
//		if ((*stack_b)->sorted_index >= highest - 35) // -31 tot -35
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//		}
//		else if ((*stack_b)->sorted_index >=highest - 40) // -36 tot -40
//			rb(stack_b);
//		else // -41 tot -45
//		     pa(stack_a, stack_b);
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		pb(stack_a, stack_b); // -41 tot -45 goed
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		rrb(stack_b); // -36 tot -40 goed
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -30 tot -35 goed
//		three--;
//	}
//	while (two)
//	{
//		if ((*stack_a)->sorted_index >= highest - 20)  // -16 tot -20
//			ra(stack_a);
//		else if ((*stack_a)->sorted_index >= highest - 25) // -21 tot -25
//		{
//			pb(stack_a, stack_b);
//			rb(stack_b);
//		}
//		else // -26 tot -30
//		     pb(stack_a, stack_b); // staat nu al goed
//		two--;
//	}
//	two = 5;
//	while (two)
//	{
//		rrb(stack_b); // -21 tot -25 goed
//		two--;
//	}
//	two = 5;
//	while (two)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -16 tot -20 goed
//		two--;
//	}
//	while (one)
//	{
//		rra(stack_a); // -1 tot -5
//		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
//				rb(stack_b);
//		}
//		one--;
//	}
//	one = 5;
//	while (one)
//	{
//		rrb(stack_b); // -6 tot -10 goed
//		one--;
//	}
//	one = 5;
//	while (one)
//	{
//		pb(stack_a, stack_b); // -1 tot -5 goed
//		one--;
//	}
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}

//int	group_lowest_B(t_node **stack_b, int count, int highest) // voor 90
//{
//	if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 91) // 160 tot 249
//	{
//		if ((*stack_b)->next)
//			rb(stack_b);
//		count++;
//	}
//	return (count);
//}

int	group_lowest_B(t_node **stack_b, int count, int highest) // voor 135
{
	if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 136) // 115 tot 249
	{
//		if ((*stack_b)->next)
//			rb(stack_b); // dalijk wegdoen 22 april
		count++;
	}
	else
		rb(stack_b); // 0 tot 114 onderaan zodat rest (die we gaan groeperen) boven staat
	return (count);
}

void	low_to_A(t_node **stack_a, t_node **stack_b, int half)
{
	int	highest;
	int	count;
	int	h;

	h = half;
	highest = half;
	count = 0;
	while (h)
	{
		if ((*stack_a)->sorted_index < half) // voeg s toe: NEE geprobeerd
		{
			pb(stack_a, stack_b);
			h--;
			count = group_lowest_B(stack_b, count, highest); // houd 90 apart
		}
		else
			ra(stack_a);
	}
//	while (count) // alles naar boven // VERANDERING BIJ 135 22 april
//	{
//		rrb(stack_b);
//		count--;
//	}
}

void	halve(t_node **stack_a, t_node **stack_b, int size)
{
	int		highest;

	highest = size / 2;
	low_to_A(stack_a, stack_b, highest); // split en houdt 135 apart, 115-249 bovenaan B
	//group_sort(stack_a, stack_b, half, 90);
	split_group(stack_a, stack_b, highest, 135); // 0-90 beneden
	highest -= 45;
	sort_highest(stack_a, stack_b, highest); 
	sort_medium(stack_a, stack_b, highest); 
	sort_lowest(stack_a, stack_b, highest);
	int count = 90;
	while (count)
	{
		rrb(stack_b);
		count--;
	}
	highest += 45;
	split_group(stack_a, stack_b, highest, 90); // 45 beneden
	sort_highest(stack_a, stack_b, highest);
	sort_medium(stack_a, stack_b, highest);
	sort_lowest(stack_a, stack_b, highest);
	sort_rest(stack_a, stack_b, highest); // sorteert laatste 45
}

void	sort_highest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 60;
	while (count > 30)
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
	while (count > 20) // -81 tot -85 op goeie plek zetten
	{
		rrb(stack_b);
		if ((*stack_b)->sorted_index > highest - 81) // -76 tot -80 naar A
			pa(stack_a, stack_b);
		count--;
	}
	while (count > 15) // -76 tot -80 op goeie plek zetten
	{
		pb(stack_a, stack_b);
		count--;
	}
	while (count)
	{
		rra(stack_a); // alles naaar boven
		count--;
	}
}

void	sort_medium(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 25;
	while (count > 10) // -61 tot -75 op goeie plek zetten
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
	while (count > 5)
	{
		rrb(stack_b); // -66 tot -70 op goeie plek zetten
		count--;
	}
	while (count)
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -61 tot -65 op goeie plek zetten
		count--;
	}
}

void	sort_lowest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count = 15;
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
}

void	split_group(t_node **stack_a, t_node **stack_b, int highest, int size) // bij 135
{
	int	count;

	count = size;
	while (count)
	{
		if ((*stack_b)->sorted_index > highest - (size - 44)) // -0 tot -90 naar beneden voor later (160-249)
			rb(stack_b);
		else if ((*stack_b)->sorted_index < highest - (size - 30)) // -106 tot -135 bovenaan A (115-145)
			pa(stack_a, stack_b);
		else                                             // -90 tot -105 onderaan A (145-160)
		{
			pa(stack_a,stack_b);
			ra(stack_a);
		}
		count--;
	}
}

//void	split_group(t_node **stack_a, t_node **stack_b, int highest, int size) // bij 90
//{
//	int	count;
//
//	count = size;
//	while (count)
//	{
//		if ((*stack_b)->sorted_index > highest - (size - 44)) // -1 tot -45 naar beneden voor later
//			rb(stack_b);
//		else if ((*stack_b)->sorted_index < highest - (size - 30)) // -61 tot -90 bovenaan A
//			pa(stack_a, stack_b);
//		else                                             // -46 tot -60 onderaan A
//		{
//			pa(stack_a,stack_b);
//			ra(stack_a);
//		}
//		count--;
//	}
//}

void	sort_rest(t_node **stack_a, t_node **stack_b, int highest)
{
	int	count;

	count = 125;
	while (count > 80) // 45
	{
		rrb(stack_b); // -31 tot -45 blijft in B
		count--;
		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
		{
			pa(stack_a, stack_b);
			ra(stack_a);
		}
		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
			pa(stack_a, stack_b);
	}
	while (count > 65) // 15
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
		count--;
	}
	while (count > 60) // 5
	{
		pb(stack_a, stack_b); // -41 tot -45 goed
		count--;
	}
	while (count > 55) //5
	{
		rrb(stack_b); // -36 tot -40 goed
		count--;
	}
	while (count > 50) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -30 tot -35 goed
		count--;
	}
	while (count > 35) // 15
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
		count--;
	}
	while (count > 30) // 5
	{
		rrb(stack_b); // -21 tot -25 goed
		count--;
	}
	while (count > 25) // 5
	{
		rra(stack_a);
		pb(stack_a, stack_b); // -16 tot -20 goed
		count--;
	}
	while (count > 10) // 15
	{
		rra(stack_a); // -1 tot -5
		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(stack_a, stack_b);
			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
				rb(stack_b);
		}
		count--;
	}
	while (count > 5) // 5
	{
		rrb(stack_b); // -6 tot -10 goed
		count--;
	}
	while (count) // 5
	{
		pb(stack_a, stack_b); // -1 tot -5 goed
		count--;
	}
	highest--; // naar juiste index
	big_list(stack_a, stack_b, highest); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
}

void	group_sort(t_node **stack_a, t_node **stack_b, int highest, int size)
{
	split_group(stack_a, stack_b, highest, size);
	sort_highest(stack_a, stack_b, highest);
	sort_medium(stack_a, stack_b, highest);
	sort_lowest(stack_a, stack_b, highest);
	sort_rest(stack_a, stack_b, highest);
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

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // goed bij 500, bij 100 aanpassen (niet 45x rrb aan begin, maar 5x rb) 
//{
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
//			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 46) // kleiner dan 49 en groter dan 24 (49 - 25)
//			{
//				if ((*stack_b)->next)
//					rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	int one = 0; // 10
//	int two = 0; // 10
//	printf("count:%d\n", count);
//	printf("%d\n", highest);
//	//print_list(*stack_b, 'B');
//	while (count)
//	{
//		rrb(stack_b); // -31 tot -45 blijft in B
//		count--;
//		if ((*stack_b)->sorted_index > highest - 16) // begin: -1 tot -15
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			one++;
//		}
//		else if ((*stack_b)->sorted_index < highest - 15 && (*stack_b)->sorted_index > highest - 31) // -16 tot -30
//		{
//			pa(stack_a, stack_b);
//			two++;
//		}
//	}
//	//print_list(*stack_a, 'A');
//	//print_list(*stack_b, 'B');
//	int three = 15;
//	while (three)
//	{
//		if ((*stack_b)->sorted_index >= highest - 35) // -31 tot -35
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//		}
//		else if ((*stack_b)->sorted_index >=highest - 40) // -36 tot -40
//			rb(stack_b);
//		else // -41 tot -45
//		     pa(stack_a, stack_b);
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		pb(stack_a, stack_b); // -41 tot -45 goed
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		rrb(stack_b); // -36 tot -40 goed
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -30 tot -35 goed
//		three--;
//	}
////	print_list(*stack_b, 'B');
//	while (two)
//	{
//		if ((*stack_a)->sorted_index >= highest - 20)  // -16 tot -20
//			ra(stack_a);
//		else if ((*stack_a)->sorted_index >= highest - 25) // -21 tot -25
//		{
//			pb(stack_a, stack_b);
//			rb(stack_b);
//		}
//		else // -26 tot -30
//		     pb(stack_a, stack_b); // staat nu al goed
//		two--;
//	}
//	two = 5;
//	while (two)
//	{
//		rrb(stack_b); // -21 tot -25 goed
//		two--;
//	}
//	two = 5;
//	while (two)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b); // -16 tot -20 goed
//		two--;
//	}
//	while (one)
//	{
//		rra(stack_a); // -1 tot -5
//		if ((*stack_a)->sorted_index < highest - 5) // -11 tot -15 gelijk goed
//		{
//			pb(stack_a, stack_b);
//			if ((*stack_b)->sorted_index >= highest - 10) // -6 tot -10
//				rb(stack_b);
//		}
//		one--;
//	}
//	one = 5;
//	while (one)
//	{
//		rrb(stack_b); // -6 tot -10 goed
//		one--;
//	}
//	one = 5;
//	while (one)
//	{
//		pb(stack_a, stack_b); // -1 tot -5 goed
//		one--;
//	}
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // bij 500 onder 9000, 100 some boven 100, dus beter zonder optimalisatie
//{
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
//			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 31) // kleiner dan 49 en groter dan 34 (49 - 35)
//			{
//				rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	int one = 0; // 10
//	int two = 0; // 10
//	printf("count:%d\n", count);
//	printf("%d\n", highest);
////	print_list(*stack_b, 'B');
//	while (count)
//	{
//		rrb(stack_b);
//		count--;
//		if ((*stack_b)->sorted_index > highest - 11) // als ie wel aan het begin te pakken is onderaan A, -1 tot -10
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			one++;
//		}
//		else if ((*stack_b)->sorted_index < highest - 10 && (*stack_b)->sorted_index > highest - 21) // -11 tot -20
//		{
//			pa(stack_a, stack_b);
//			two++;
//		}
//	}
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');
//	int three = 10;
//	while (three) // begint bovenaan B
//	{
//		if ((*stack_b)->sorted_index >= highest - 25) //onderste naar onder
//			rb(stack_b);
//		else
//			pa(stack_a, stack_b); // bovenste naar a
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		pb(stack_a, stack_b);
//		three--;
//	}
//	three = 5;
//	while (three)
//	{
//		rrb(stack_b);
//		three--;
//	}
//	while (two)
//	{
//		if ((*stack_a)->sorted_index >= highest - 15)
//			ra(stack_a);
//		else
//			pb(stack_a, stack_b);
//		two--;
//	}
//	two = 5;
//	while (two) // two compleet
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b);
//		two--;
//	}
//	while (one)
//	{
//		rra(stack_a);
//		if ((*stack_a)->sorted_index < highest - 5)
//			pb(stack_a, stack_b);
//		one--;
//	}
//	one = 5;
//	while (one)
//	{
//		pb(stack_a, stack_b);
//		one--;
//	}
//	print_list(*stack_a, 'A');
//	print_list(*stack_b, 'B');
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}

//int	random_split(t_node **stack_a, t_node **stack_b, int size) // werkt beter dan die hieronder
//{
//	//static 	int	arr[5] = {0};
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
//			if ((*stack_b)->sorted_index < highest && (*stack_b)->sorted_index > highest - 16) // kleiner dan 49 en groter dan 34 (49 - 35)
//			{
//				rb(stack_b);
//				count++;
//			}
//		}
//		else
//			ra(stack_a);
//	}
//	int one = 0;
//	int two = 0;
//	printf("count:%d\n", count);
//	printf("%d\n", highest);
//	print_list(*stack_b, 'B');
//	while (count)
//	{
//		rrb(stack_b);
//		count--;
//		if ((*stack_b)->sorted_index > highest - 6) // als ie wel aan het begin te pakken is onderaan A, -1 tot -5
//		{
//			pa(stack_a, stack_b);
//			ra(stack_a);
//			one++;
//		}
//		else if ((*stack_b)->sorted_index < highest - 5 && (*stack_b)->sorted_index > highest - 11) // -6 tot -10
//		{
//			pa(stack_a, stack_b);
//			two++;
//		}
//	}
//	print_list(*stack_b, 'B');
//	while (two)
//	{
//		pb(stack_a, stack_b);
//		two--;
//	}
//	while (one)
//	{
//		rra(stack_a);
//		pb(stack_a, stack_b);
//		one--;
//	}
//	print_list(*stack_b, 'B');
//	half--; // naar juiste index
//	big_list(stack_a, stack_b, half); // 100 nummers 600 operations (700 = 100% 1100 = 80%)
//	operations = count_operations("");
//	return (operations);
//}

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
