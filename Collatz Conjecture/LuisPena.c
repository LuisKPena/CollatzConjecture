/*
 * This is a program that receives an int and  applies 
 * the Collatz Conjecture algorithm to it in separate 
 * child processes using the fork() system call.
 *
 * @author Luis Pena (PID 6300130)
 * @version 05/16/2023
 *
 * Question 2 Answer: The processes do not always finish
 * in the order in which they are forked because they are
 * interleaved, thus the order of execution is impacted
 * by processes such as speed of each child and by the 
 * priorities of the O.S. scheduler. The latter, in particular,
 * programmers do not have control over, causing much variation. 
 * Thefore this same code will execute the forks differently
 * on different machines/O.S.s.
 *
 */
 
//Imports
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Function to perform Collatz Conjecture and print to terminal
void collatz(int n, int child_number)
{
	//Printing child number, PID, and inital value of n
	printf("%s %d, %s = %d, %s = %d\n", "From Child", child_number, "PID", getpid(), "Init Number", n);
	
	//As long as n does not equal 1
	while(n != 1)
	{
		//If n is even divide n by 2
		if(n % 2 == 0)
		{
			n = n/2;
		}

		//Else multiply n by 3 and add 1
		else if(n % 2 != 0)
		{
			n = 3 * n + 1;
		}
		
		//Printing child number with output
		printf("%s %d: %s = %d\n", "From Child", child_number, "Number", n);	
	}

	//Printing to console to inform user that child process is done
	printf("%s %d %s\n", "Child", child_number, "is done!");
}

//Main function
int main(int argc, char *argv[])
{
	//Instantiating and intializing variables
	int n = atoi(argv[1]);
	static char usage[] = "usage: %s number [number...]\n";
	pid_t pid1, pid2;

	//Checking that a number argument has been entered
	if(argc != 2)
	{
		fprintf(stderr, "You must enter a single number argument for the Collatz Conjecture\n");
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	//Validating that input value is between 1 and 39 (inclusive)
	if(n < 1 || n > 40)
	{
		fprintf(stderr, "Please enter a number greater than 0 and less than 40.\n");
		exit(1);
	}

	//Creating first fork
	pid1 = fork();
	
	//Checking that fork could be created
	if(pid1 < 0)
	{
		fprintf(stderr, "Fork failed");
		exit(1);
	}
	
	//If fork is created then pass arguments to collatz
	else if(pid1 == 0)
	{
		collatz(n, 1);
		return 0;
	}

	//Creating second fork
	pid2 = fork();

	//Checking that fork could be created
	if(pid2 < 0)
	{		
		fprintf(stderr, "Fork failed");
		exit(1);
	}

	//If fork is created then pass arguments to collatz
	else if(pid2 == 0)
	{	
		collatz(n + 4, 2);
		return 0;
	}
		
	//Wait command for parent
	wait(NULL);
	wait(NULL);
	
	//Informing user that all child processes finished
	printf("All child processes finished!\n");

	//Returning 0 once program completes
	return 0;
}
