# Baby C Compiler
This is a project that was built in my compiler class. 
The compiler that I built was written in the C language and converts a subset of the C language, Baby C, to an intermediary assembly language known as ILOC. 
It works by taking input from a file, then uses a software called FLEX to scan the file. 
After this I generate an LR(1) grammar which combined with another software called YACC creates an abstract syntax tree (AST).
Based off of this AST, I use depth first search and recursion to create ILOC.
I keep track of variable names and assignments by using a lookup table. 
Due to the nature of this assignment, I used a linked list for the lookup table because of it was simple to implement. 
However, the lookup table would have been more efficient if I used a hash table instead.
# What I Learned
- Became more comfortable developing in the C language and using pointers
- Practical uses for algorithms such as Depth First Search
- Practical uses for data structures such as linked lists, hash tables, graphs, and trees
- The compilation process
- Regular expressions and how to create grammars in code
- LR(1) and LL(1) parsing
