This is a simple experimental program I whipped up in a few minutes.  
The basic idea is that it is a universal solver for predicting the next 
element in a sequence of integers.  

The theory behind it is that you want to find the rule for generating 
the sequence that has the least Kolmogorov complexity (see Wikipedia for 
definition).  The types of rules that I look for are brainfuck programs 
(without input).  Very simply, the shorter programs are considered less 
complex.  Thus jsequence-solver will find the shortest brainfuck program 
that will output a given sequence of integers.  From this, you can guess 
what the next likely output would be, assuming it follows this rule.  
Theoretically this will solve any sequence.  The time it takes, however, 
is a different matter... maybe in the future it will be feasible for 
moderate complexity sequences.  Right now it will only solve very basic 
ones like 1 2 3 2 3 4.  In fact, getting it to output just the number 12 
is a struggle.

To build:
run make from this directory

To run:
./sequencesolver 1 0 2 3

or whatever sequence you want it to solve other than 1 0 2 3.

It will output the brainfuck program, and you will have to run the 
brainfuck program through some other means to get the full sequence it 
predicts.

Future and stuff: 
Maybe I will make it multithreaded in the future, as this is an 
immensely parallel task.

Halting problem: 
Some of you may think "Wait a minute! You can't tell when a program goes 
into an infinite loop!  This is theoretically impossible!"  True, true, 
but I figure if a program doesn't output for 50 instructions, I didn't 
really care what it had to say anyway.  That limit should be raised when 
there is enough computing power to actually predict complex sequences 
that might take more than 50 instructions to generate each integer.


License:
Released under the WTFPL

