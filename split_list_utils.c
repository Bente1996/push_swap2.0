/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   split_list_utils.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/05/25 17:00:09 by bede-kon            #+#    #+#           */
/*   Updated: 2026/05/25 18:30:25 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	move_highest(int *arr, int highest)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 3 && arr[i] != 0)
		sum += arr[i++];
	if (sum == 1)
		highest--;
	else if (sum == 11)
		highest -= 2;
	else if (sum == 111)
		highest -= 3;
	else
		return (highest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(highest);
}

int	move_lowest(int *arr, int lowest)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 3 && arr[i] != 0) // 5 naar 3 veranderen
		sum += arr[i++];
	if (sum == 1)
		lowest++;
	else if (sum == 11)
		lowest += 2;
	else if (sum == 111)
		lowest += 3;
	else
		return (lowest);
	check_shift(arr, sum); // give right values based on shift 5->4 for sum == 1
	return(lowest);
}

void	check_shift(int *arr, int sum)
{
	int	i;

	i = 2;
	if (sum == 1) // dan was de tweede dus sowieso niet gevonden, 3e mss wel
		shift_group(arr, 1);
	else if (sum == 11)
		shift_group(arr, 2); 
	else if (sum == 111)
		shift_group(arr, 3);
	while (sum >= 1) // zet nodige arrays op 0
	{
		arr[i--] = 0;
		sum /= 10;
	}
}

void	shift_group(int *arr, int n)
{
	int	shrink;
	int	i;

	i = 0;
	shrink = 1;
	while (i + n < 3) // 5 naar 3 veranderen
	{
		if (arr[i + n])
			arr[i] = arr[i + n] - (shrink * 9);
		else
			arr[i] = 0;
		i++;
		shrink *= 10;
	}
}
