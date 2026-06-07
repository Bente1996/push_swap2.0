/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/03/12 20:16:17 by bede-kon            #+#    #+#           */
/*   Updated: 2026/03/12 20:16:20 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_node	*A;
	t_node	*B;
	int		index;

	A = NULL;
	B = NULL;
	index = 0;
	if (argc < 3)
		return (1);
	A = make_list(argc, argv, &index);
	if (!A)
		return (1);
	if (!already_sorted(A))
		sort_all(&A, &B, index);
	free_list(A);
	return (0);
}
