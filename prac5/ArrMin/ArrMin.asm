// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@1 // sets first element to current lowest value
A=M
D=M
@0
M=D

(LOOP)

@R0 // fetch min val
D=M

@SETR4 // set R4
D;JGE
@R4
M=1
(R4SET)

@1 // access current index in array
A=M
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
@SKIP
D;JGT

(COMP)
@1
A=M
D=M // check if accessed index has the current lowest value. If not, jumps to SKIP
@0
D=D-M
@SKIP
D;JGT

(SWAP)
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

(END)
0;JMP