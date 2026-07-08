*This project has been created as part of the 42 curriculum by bede-kon.*


# Description:
In this project you need to sort a list of integers, conforming to a few rules:
- you have at your disposal two stacks and a set of instructions (operations) to
  manipulate both stacks
- your program displays the operations needed to sort given integers, 
  trying to limit the amount as much as possible (not surpassing the given 
  benchmarks)

# Instructions:
You can compile the project by typing ```make``` in the terminal.

You can run the program by typing ```./push_swap [INT] [INT]...``` in the 
terminal.

When testing in how many operations the program sorts the stack, you can type:
``` ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l" ```

When testing whether the stack is properly sorted, you can use the given
tester:
``` ARG="4 67 3 87 23"; ./push_swap | ./checker_linux $ARG" ```
If the stack is sorted correctly it will display OK, otherwise KO.

# Resources:
The only algorithm that I implemented was selection sort for lists that contain
20 or less integers:
https://www.geeksforgeeks.org/dsa/selection-sort-algorithm-2/

Bigger lists are sorted by looking for small chunks of integers at a time:
- medium sized lists (21-149) are sorted by splitting the list in half and then
sorting those halfs by looking for six integers at a time (two groups of three: 
e.g. 22 23 24 and 47 48 49), ordering them correctly

- bigger lists (150+) are sorted by splitting the list in half and then
organising part of the list in chunks of five (e.g. 1 4 0 2 3 8 5 6 9 7 etc.),
then sorting the list correctly by looking for five integers at a time

Because for bigger lists I'm splitting the list up, I'm making use of some kind 
of distribution sort algorithm:
https://en.wikipedia.org/wiki/Sorting_algorithm#Distribution_sorts

I haven't made use of AI for this project.
