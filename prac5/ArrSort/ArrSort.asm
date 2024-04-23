// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

(LOOP)
@R0 // set R0 to 0
M=A 

(SORT) // float the next greatest value to its position in the array

@R0 // check if at end of array
D=M
@R2
D=M-D
D=D-1
@ARRAYEND
D;JEQ

@R0
D=M
@1 // find index
A=M+D

//comparison section
D=M // if both numbers are negative, jump to COMP
A=A+1
D=D&M
@COMP
D;JLT

@R0
D=M
@1 // find index
A=M+D

D=M // if both numbers are positive, jump to COMP
A=A+1
D=D|M
@COMP
D;JGT

(NCHECK) // if index value positive, jump to SWAP; else jump to SKIP
@R0
D=M
@1 // find index
A=M+D
D=M
@SWAP
D;JGE
@SKIP
0;JMP

(COMP)
@R0
D=M
@1 // find index
A=M+D
D=M // if next element is lesser, then swap. 
A=A+1
D=M-D
@SWAP
D;JLT

(SKIP)
@R0 //Else continue traversing until end of array
M=M+1

@SORT
0;JMP

(SWAP) // swap values in two adjacent indexes
@0 // find index
D=M
@1
A=D+M

D=M // execute swap
A=A+1
D=D+M
M=D-M
A=A-1
M=D-M

@R0 //increment R0
D=D+1

@SORT
0;JMP

(ARRAYEND) //Handles end of array

@R2 // if length is 1 end program
M=M-1
D=M
@ENDLOOP
D;JEQ

@LOOP // else jump to LOOP
D;JMP

(ENDLOOP)

@1 // set R0 to -1
D=!A 
@R0
M=D+1

@ENDPROGRAM
(ENDPROGRAM)
0;JMP