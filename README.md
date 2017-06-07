# Best_Soluton_Frogs_Toads

Problem Statement:
This program is to implement the simplified version of Frogs and Toads game with two
algorithms. Also, it will examine the effectiveness of the A* searching algorithm compared with
the Brand & Bound search and summarize the difference and efficiency.


Assumption:
This program only works for 2x2 or 3x3 Frogs and Toads game.


Design Report:
The most important data structure for this program is struct which contains 6 variables –
underestimate, distance_travelled, total_path, gap_position, vector frogs_toads, and double
vector solution.
• Underestimate: There is function called get_underestimate(). It counts how many
elements displaced in vector frogs_toads compared with the initial vector. This variable
will be used to calculate the total path in A* algorithm.
• Distance_travelled: It keeps tracking how many steps has the state travelled in a tree
structure. This variable will be used in both A* and Brand&Bound algorithm.
• Total_path: underestimate + distance_travelled. This variable is only used in A*
algorithm.
• Gap_position: it keeps tracking where is the space is after moving or jumping.
• Vector frogs_toads: the movement of the frogs and toads in the vector.
• Double vector solution: the double vector solution stores all the vectors of frogs_toads
when it changes.

A* algorithm
First it will check if the vector is the final solution. If not, it will increase the number of loops
which can be used as evidence for the effectiveness comparison. Also, it will get the current state
from the top of the queue for expand purpose. It will pop off after. Then, the program will check
for all the element in the vector that in that current state. If it can be moveable to right or left, or
can jump to right or left. It will copy the state to a priority queue for printing out the path
purpose. Then, it will store the updated total path and all updated variables in the struct.
The updated path is sorted based on the total distance which is the sum of underestimate plus the
distance travelled defined in the struct data structure.

Other data structure is vector in which the element is the states. It stores all the states that have
been visited. In this way, the program can check if the current state in the expanded level is
visited. If yes, the current state will not be expanded and will not be placed in the priority queue.
Which makes sure to reduce the redundant path. It is required in A* algorithm.

Brand&Bound algorithm
In this program, the Brand&Bound algorithm is similar with the A* algorithm. The differences
are the calculation of the total distance and the redundant path. In Brand&Bound, it does not
reduce the redundant, and the total distance is the distance travelled. There is no estimated
distance to the goal.
