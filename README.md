# Parallel-Processing-Assignments
------------------------------------------

# Assignment 1
Students should write a parallel c program for “Counting Primes” using the 
following two methods: MPI_Send and MPI_Receive ONLY 
Given  
- Lower bound number x 
- Upper bound number y 
Output  
- Count of prime numbers occurring between x and y 
- Count of prime numbers occurring in each process. 


# Assignment 2
Write a parallel c program to calculate standard deviation using MPI_Bcast, MPI_Reduce
& MPI_Allreduce ONLY. Don’t use MPI_Send and MPI_Receive
Given:
An integer n (number of elements per each process).
Output:
Standard deviation of randomly generated (n * numberOfProcesses) elements.


# Assignment 3
Write a parallel C program using OpenMP such that :
Given a matrix where every element is either ‘O’ or ‘X’, replace ‘O’ with ‘X’ if surrounded
by ‘X’. A ‘O’ (or a set of ‘O’) is considered to be surrounded by ‘X’ if there are ‘X’ at
locations just left and just right of it.
O’s at the edges will not be replaced
You should handle invalid input.
Sample input :
6 5 Sample output :
X O X| X X X X X X X
X O X| O X X X X X X
O X O| O X O X O O X
- - - 
X X X X X X X X X X
X O O X X X O O X X
O X O X O O X X X O
![image](https://user-images.githubusercontent.com/36418892/176719047-c1827f99-1e3a-48a8-8307-506e7086e3d4.png)



# Assignment 4
MPI & OpenMP
Sum of Convergent Series
Write c code to solve this problem using hybrid programming.
This problem from n = 1 to infinite will converge to 1 at the end try to reach this result
and print the error value as your expected result = 1 ( error = expected - calculated)


# To run these programs you need virtual machine like VirtualBox
