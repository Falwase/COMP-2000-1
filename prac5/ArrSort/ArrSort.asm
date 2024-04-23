// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// R3 for current index

// Put your code here.

(LOOP)
@R1 // R3 is used to track current index, initialise R3 at R1 
D=M
@R3
M=D

(SORT)
@R2 // checks if end of array is reached
D=M
@R1
D=D+M
@R3
D=D-M
D=D-1
@ARRAYEND
D;JEQ

@R3 // find current index
A=M
D=M

@SETR4 // set R4
D;JGE
@R4
M=1
(R4SET)

@R3 // find next index
A=M+1
D=M

@SETR5 // set R5
D;JGE
@R5
M=1
(R5SET)

@R4 // if R4 is + and R5 is -, jump to SWAP; else if R4 is - and R5 is +, jump to PASS; else, continue
D=M
@R5
D=D-M
@SWAP
D;JLT
@PASS
D;JGT

@R3 // if R4 > R5, jump to SWAP; else continue
A=M
D=M
A=A+1
D=D-M
@SWAP
D;JGT

(PASS) // increment index
@R3
M=M+1
@SORT
0;JMP

(SETR4)
@R4
M=0
@R4SET
0;JMP

(SETR5)
@R5
M=0
@R5SET
0;JMP

(SWAP) // swaps two adjacent elements in the list
@R3
A=M
D=M
A=A+1
D=D+M
M=D-M
A=A-1
M=D-M
@PASS
0;JMP

(ARRAYEND) // handles end of array; if R2 = 1, jump to ENDSORT; else jump to LOOP
@R2
M=M-1
D=M
D=D-1
@ENDSORT
D;JEQ
@LOOP
0;JMP

(ENDSORT)
@R0
M=0
M=M-1

@END
(END)
0;JMP