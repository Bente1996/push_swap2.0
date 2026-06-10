/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   lowering.c                                              :+:    :+:       */
/*                                                          +:+               */
/*   By: bede-kon <bede-kon@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2026/06/08 17:41:06 by bede-kon            #+#    #+#           */
/*   Updated: 2026/06/08 17:48:51 by bede-kon            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>



void	try_third(t_stats *data, t_node **A)
{
	data->bottom_stack = check_bottom(*A);
	if (data->bottom_stack->n_index == (*A)->n_index - 1)
	{
		rra(A, data->top);
		rra(A, data->top);
		sa(A, data->top);
		data->lower--;
		data->bottom--;
	}
	if ((*A)->n_index != (*A)->next->n_index - 1)
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
	else
	{
		data->bottom--;
		data->bottom_stack = NULL;
		data->lower--;
	}
}

void	check_third(t_stats *data, t_node **A)
{
	data->lower--;
	data->bottom--;
	if (data->bottom_stack->n_index == (*A)->n_index - 1) // maak ff 1 statement
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
	}
	data->bottom_stack = NULL;
}

bool	add_second(t_stats *data, t_node **A)
{
	if (data->bottom_stack->n_index == (*A)->n_index - 1) // tweede mag ook
	{
		rra(A, data->top);
		data->bottom--;
		data->lower--;
		if (data->bottom)
			data->bottom_stack = find_bottom(*A);
		else
			data->bottom_stack = NULL;
		if (data->bottom && data->bottom_stack->n_index == (*A)->n_index - 1)
		{
			rra(A, data->top);
			data->lower--;
			data->bottom_stack = NULL;
			data->bottom--;
		}
		return (true);
	}
	else
		return (false);
}

void	add_third(t_stats *data, t_node **A)
{
	rra(A, data->top);
	sa(A, data->top);
	data->lower--;
	data->bottom--;
	if ((*A)->n_index == (*A)->next->n_index - 1)
	{
		data->lower--;
		data->bottom--;
		data->bottom_stack = NULL;
	}
	else
	{
		ra(A, data->top);
		data->bottom_stack = find_bottom(*A);
	}
}

#include <stdio.h>


//CASE:
//./push_swap 564 130 820 657 407 554 307 817 382 416 209 285 534 226 170 393 855 796 791 415 250 341 977 291 949 372 700 601 765 457 655 573 986 66 626 420 72 178 498 414 93 56 388 575 997 846 169 114 942 330 428 410 139 992 664 797 132 665 155 159 405 650 708 532 151 681 301 342 515 163 459 375 294 419 973 786 6 773 886 216 706 680 984 401 643 166 806 422 603 715 514 695 961 433 340 437 16 54 639 271 798 362 374 560 833 215 235 259 621 726 230 377 916 709 516 149 940 90 462 776 859 477 19 158 444 508 135 697 867 861 689 935 434 20 822 211 97 296 787 426 774 265 126 900 557 168 383 102 472 458 845 753 49 594 138 94 487 197 906 60 450 446 925 995 184 105 221 828 509 743 656 588 795 981 325 785 440 312 281 734 519 936 631 202 404 756 924 849 570 582 258 467 683 834 423 970 309 779 25 917 623 716 113 794 338 140 223 589 179 746 784 134 431 18 191 923 456 685 599 110 595 238 964 932 669 499 398 201 954 990 460 239 298 409 593 173 116 408 880 762 904 481 666 304 740 982 592 120 800 367 751 373 638 926 387 125 40 57 490 429 117 890 186 400 989 88 985 425 677 203 728 112 172 445 68 907 147 365 672 827 62 337 471 909 334 567 356 287 881 469 354 121 128 702 495 47 324 717 22 133 759 852 574 591 328 427 303 67 152 357 89 277 26 63 443 712 261 929 719 7 976 613 742 83 402 803 956 268 37 441 523 274 41 124 872 920 824 590 92 931 205 902 380 492 167 891 914 182 153 463 77 295 260 228 397 807 75 943 363 748 636 194 654 783 190 579 290 455 448 628 868 767 8 106 871 154 604 611 58 561 127 842 96 696 231 597 246 318 200 887 969 711 145 468 361 531 292 730 945 189 622 648 242 486 368 36 84 939 177 299 198 306 614 252 192 496 825 348 104 262 485 269 951 538 451 289 417 504 647 536 323 975 821 254 544 111 967 830 790 240 870 766 321 80 305 732 957 537 960 358 627 805 718 529 851 581 780 273 678 549 473 418 816 389 279 366 255 811 684 993 503 713 866 390 863 406 934 171 850 91 792 809 652 61 760 45 336 87 220 757 856 804 848 510 100 272 843 670 465 801

void	get_third(t_stats *data, t_node **A)
{
	printf("A EERST: %d\n", (*A)->n_index);
	printf("A->next EERST: %d\n", (*A)->next->n_index);
	printf("BOttom EERst; %d\n", data->bottom_stack->n_index);
	if ((*A)->n_index == 445)
		print_list(*A, 'A');
	rra(A, data->top);
	sa(A, data->top);
	ra(A, data->top);
	sa(A, data->top);

//	rra(A, data->top); // alle 3 nu boven
//	if (!((*A)->n_index == (*A)->next->n_index - 1))
//		sa(A, 0);
//	data->bottom_stack = NULL;
//	data->bottom -= 2;
//	data->lower -= 3;
	printf("bottom VOOR: %d\n", data->bottom);
	printf("lower VOOR: %d\n", data->lower);
//	printf("bottom: %d\n", data->bottom);
	data->bottom_stack = find_bottom(*A);
	printf("a: %d\n", (*A)->n_index);
	printf("a->next: %d\n", (*A)->next->n_index);
	printf("bottom: %d\n", data->bottom_stack->n_index);
	if ((*A)->n_index == (*A)->next->n_index - 1) // check if bottom fits too
		funk(data, A);
	else if (data->bottom_stack->n_index == (*A)->next->n_index - 1) // get
																	 // bottom
																	 // move 1
																	 // down
		fonk(data, A);
	else
	{
		if ((*A)->n_index > data->bottom_stack->n_index)
			data->bottom_stack = *A;
		ra(A, data->top);
	}
	if (data->bottom == 1)
		print_list(*A, 'A');
	printf("bottom NA: %d\n", data->bottom);
	printf("lower NA: %d\n", data->lower);
	printf("a NA: %d\n", (*A)->n_index);
	printf("a->next NA: %d\n", (*A)->next->n_index);
	if (data->bottom)
		printf("bottom NA: %d\n", data->bottom_stack->n_index);
}
