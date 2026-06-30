/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   print_operations.c                                      :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/30 22:21:36 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/30 22:35:27 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int	check_rotate(t_text *before_last, t_text *last, const char *op)
{
	if ((!strcmp(op, "ra") && !strcmp(last->text, "rb"))
		|| (!strcmp(op, "rb") && !strcmp(last->text, "ra")))
		last->text = "rr";
	else if ((!strcmp(op, "ra") && !strcmp(last->text, "rra"))
		|| (!strcmp(op, "rb") && !strcmp(last->text, "rrb"))
		|| (!strcmp(op, "rr") && !strcmp(last->text, "rrr")))
	{
		before_last->next = NULL;
		free(last);
	}
	else
		return (0);
	return (1);
}

int	check_r_rotate(t_text *before_last, t_text *last, const char *op)
{
	if ((!strcmp(op, "rra") && !strcmp(last->text, "rrb"))
		|| (!strcmp(op, "rrb") && !strcmp(last->text, "rra")))
		last->text = "rrr";
	else if ((!strcmp(op, "rra") && !strcmp(last->text, "ra"))
		|| (!strcmp(op, "rrb") && !strcmp(last->text, "rb"))
		|| (!strcmp(op, "rrr") && !strcmp(last->text, "rr")))
	{
		before_last->next = NULL;
		free(last);
	}
	else
		return (0);
	return (1);
}

int	check_swap(t_text *before_last, t_text *last, const char *op)
{
	if ((!strcmp(op, "sa") && !strcmp(last->text, "sb"))
		|| (!strcmp(op, "sb") && !strcmp(last->text, "sa")))
		last->text = "ss";
	else if ((!strcmp(op, "sa") && !strcmp(last->text, "sa"))
		|| (!strcmp(op, "sb") && !strcmp(last->text, "sb"))
		|| (!strcmp(op, "ss") && !strcmp(last->text, "ss")))
	{
		before_last->next = NULL;
		free(last);
	}
	else
		return (0);
	return (1);
}

int	check_push(t_text *before_last, t_text *last, const char *op)
{
	if ((!strcmp(op, "pa") && !strcmp(last->text, "pb"))
		|| (!strcmp(op, "pb") && !strcmp(last->text, "pa")))
	{
		before_last->next = NULL;
		free(last);
	}
	else
		return (0);
	return (1);
}
