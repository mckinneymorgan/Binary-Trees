README for Program 2: Trees
Original author: Morgan McKinney 2/2020

trees.cpp:

Program is intended to create two binary trees and output each data point on
each tree using symmetric and postorder traversal. The first tree is created
using standard input, while the second tree is created by traversing the first
in preorder. Finally, the program reads one more integer from standard input:
the probe. The program searches for the probe in the second tree and outputs
the closest point it can find.

Before anything else, make sure to compile the program. This can be done
using the Makefile: "make run". This will link all the necessary files
in order to run trees.cpp correctly. Furthermore, it will automatically
run the program with a predetermined number of points (10) and seed (43) for
randomly generated standard input. The output will be placed in tmpRun.out.

In order to invoke the program after intial compilation:
"./randGen.pl # | ./trees.cpp # > tmpRun.out"
The pound signs represent the standard input seed and number of points
respectively. Both are up to the discretion of the user. To reiterate,
the output will be placed in tmpRun.out.

tmpRun.out:

Temporary output file detailing each point (X, Y, Z) outputted by trees.cpp.
Can be read using the 'cat' command.

Makefile:

Present for easy user compilation of trees.cpp. Input varies by desired
output:
"make run" to compile and run trees.cpp with default inputs; installs randGen.pl
"make workingTrees" to compile and run a working program with default inputs
