#include "push_swap.h"

void	sort_forty_five(t_node **A, t_node **B, int half, int size)
{
	int	count;

	count = size;
	while (count--)
	{
		if ((*B)->n_index > half - (size - 44)) // (115-250)
			rb(B, 0);
		else if ((*B)->n_index < half - (size - 30)) // (99-70)
			pa(A, B, 0);
		else                                             // (100-114)
		{
			pa(A,B, 0);
			ra(A, 0);
		}
	}
	sort_low(A, B, half - (size - 90), 60); 
	sort_medium(A, B, half - (size - 90), 25); 
	sort_high(A, B, half - (size - 90), 25);
}

void	sort_low(t_node **A, t_node **B, int highest, int count)
{
	while (count > 30) // 30
	{
		if ((*A)->n_index > highest - 76) // -61 tot -75 onderaan A
			ra(A, 0);
		else                                       // -76 tot -90 bovenaan B
		{
			pb(A, B);
			if ((*B)->n_index > highest - 86) // -76 tot -85 naar beneden, -86 tot -90 al goed!
				rb(B, 0);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 20) // -81 tot -85 op goeie plek
		{
			rrb(B);
			if ((*B)->n_index > highest - 81) // -76 tot -80 naar A
				pa(A, B, 0);
		}
		else if (count >= 15) // -76 tot -80
			pb(A, B);
		else                  // alles naar boven
			rra(A, 0);
	}
}

void	sort_medium(t_node **A, t_node **B, int highest, int count)
{
	while (count > 10) // -61 tot -75 op goeie plek zetten
	{
		if ((*A)->n_index < highest - 65) // -66 tot -75 naar B
		{
			pb(A, B);
			if ((*B)->n_index > highest - 71) // -66 tot -70 onderaan B, -71 tot -75 op goeie plek
				rb(B, 0);
		}
		else // -61 tot -65 onderaan A
		     ra(A, 0);
		count--;
	}
	while(count--)
	{
		if (count >= 5)  // -66 tot -70
			rrb(B);
		else              // -61 tot -65
		{
			rra(A, 0);
			pb(A, B);
		}
	}
}

void	sort_high(t_node **A, t_node **B, int highest, int count)
{
	while (count > 10) // -46 tot -60 op goeie plek zetten
	{
		rra(A, 0); // alles naar boven
		if ((*A)->n_index < highest - 50) // -51 tot -60 op goeie plek zetten
		{
			pb(A, B); // -56 tot -60 staat goed
			if ((*B)->n_index > highest - 56) // -51 tot -55 naar beneden
				rb(B, 0);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -51 tot -55
			rrb(B);
		else            // -46 tot -50
			pb(A, B);
	}
}

void	groups_of_fifteen(t_node **A, t_node **B, int highest, int count)
{
	while (count--) // 45
	{
		rrb(B); // -31 tot -45 blijft in B
		if ((*B)->n_index > highest - 16) // begin: -1 tot -15
		{
			pa(A, B, 0);
			ra(A, 0);
		}
		else if ((*B)->n_index < highest - 15 && (*B)->n_index > highest - 31) // -16 tot -30
			pa(A, B, 0);
	}
}

void	sort_fifteen_A(t_node **A, t_node **B, int highest, int count)
{
	while (count > 15) // 15
	{
		if ((*B)->n_index >= highest - 35) // -31 tot -35
		{
			pa(A, B, 0);
			ra(A, 0);
		}
		else if ((*B)->n_index >=highest - 40) // -36 tot -40
			rb(B, 0);
		else // -41 tot -45
		     pa(A, B, 0);
		count--;
	}
	while (count--)
	{
		if (count >= 10) // -41 tot -45
			pb(A, B);
		else if (count >= 5) // -36 tot -40
			rrb(B);
		else             // -30 tot -35
		{
			rra(A, 0);
			pb(A, B);
		}
	}
}

void	sort_fifteen_B(t_node **A, t_node **B, int highest, int count)
{
	while (count > 10) // 15
	{
		if ((*A)->n_index >= highest - 20)  // -16 tot -20
			ra(A, 0);
		else if ((*A)->n_index >= highest - 25) // -21 tot -25
		{
			pb(A, B);
			rb(B, 0);
		}
		else // -26 tot -30
		     pb(A, B); // staat nu al goed
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -21 tot -25 goed
			rrb(B);
		else            // -16 tot -20 goed
		{
			rra(A, 0);
			pb(A, B);
		}
	}
}

void	sort_fifteen_C(t_node **A, t_node **B, int highest, int count)
{
	while (count > 10) // 15
	{
		rra(A, 0); // -1 tot -5
		if ((*A)->n_index < highest - 5) // -11 tot -15 gelijk goed
		{
			pb(A, B);
			if ((*B)->n_index >= highest - 10) // -6 tot -10
				rb(B, 0);
		}
		count--;
	}
	while (count--)
	{
		if (count >= 5) // -6 tot -10
			rrb(B);
		else            // -1 tot -5
			pb(A, B);
	}
}

void	sort_rest(t_node **A, t_node **B, int highest) // highest in struct doen (misschien)
{
	groups_of_fifteen(A, B, highest, 45);
	sort_fifteen_A(A, B, highest, 30);
	sort_fifteen_B(A, B, highest, 25);
	sort_fifteen_C(A, B, highest, 25);
}
