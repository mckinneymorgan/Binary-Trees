# CS315 Makefile for Program 2: Trees
# Feel free to modify as needed.
# Original author: Raphael Finkel 1/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g
GOAL = trees

NUMPOINTS = 10
SEED = 43

# compile and run the student program, placing the result in tmpRun.out
run: $(GOAL) randGen.pl
	./randGen.pl $(SEED) | ./$(GOAL) $(NUMPOINTS) > tmpRun.out
	less tmpRun.out

# compile and run a known working program, placing the result in tmpWorking.out
runWorking: workingTrees randGen.pl
	./randGen.pl $(SEED) | ./workingTrees $(NUMPOINTS) > tmpWorking.out
	less tmpWorking.out

# get the randGen.pl program
randGen.pl:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog1/randGen.pl
	chmod +x randGen.pl

# get the workingTrees program
workingTrees:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog2/workingTrees
	chmod +x workingTrees

# Modify the following recipe to zip exactly what you want to include.
zipAll: 
	zip toSubmit.zip $(GOAL).* Makefile README.txt tmpRun.out
	
.PHONY: clean
clean:
	rm -f randGen.pl $(GOAL) workingTrees tmp* toSubmit.zip
