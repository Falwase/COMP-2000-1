// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@1 // sets first element to current lowest value
A=M
D=M
@0
M=D

(LOOP)

@1 // access current index in array
A=M

D=M // if both numbers are negative, jump to COMP
@0
D=D&M
@COMP
D;JLT

@1 // if current index is negative, set it to as new min value; else jump to PCHECK
A=M 
D=M 
@PCHECK
D;JGE
@0
M=D
@SKIP
0;JMP

(PCHECK) //if min value negative, jump to skip; else continue
@0
D=M
@SKIP
D;JLT

(COMP)
@1
A=M
D=M // check if accessed index has the current lowest value. If not, jumps to SKIP
@0
D=D-M
@SKIP
D;JGT

@0 // sets new lowest value to R0
D=D+M
M=D

(SKIP)

@1 // increment array index
M=M+1

@2 // decrement length and jumps to LOOP if length is not one
M=M-1
D=M
@LOOP
D;JNE

@END
(END)
0;JMP