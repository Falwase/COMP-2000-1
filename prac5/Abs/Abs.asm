// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.

@1
D=M
@SKIP
D;JGE
D=!D
D=D+1
(SKIP)
@0
M=D

0;JMP