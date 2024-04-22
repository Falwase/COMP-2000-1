// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

@2 // if R2 is positive or zero then jump straight to loop
D=M
@LOOP
D;JGE

@1 // if R2 is negative negate both R1...
M=!M
M=M+1
@2 // ...and R2
M=!M
M=M+1

(LOOP) // add R1 to D R2 times

@2 // if R2 is zero skip to the end
D=M
@END
D;JEQ

@1 // add R1 to R0
D=M
@0
M=M+D

@2 // decrement R2
M=M-1

@LOOP // jump back to start of loop
0;JMP

(END)
0;JMP